//////////////////////////////////////////////////////////////////////////////////////////
//	BSP.cpp
//	Functions for bsp file
//	Downloaded from: www.paulsprojects.net
//	Created:	8th August 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#include <windows.h>
#include <stdio.h>

// #include <GL\gl.h>
// #include <GL\glu.h>
// #include <GL\glext.h>
// #include <GL\wglext.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// #include "LOG.h"
// #include "extensions/ARB_multitexture_extension.h"
// #include "extensions/EXT_draw_range_elements_extension.h"
// #include "extensions/EXT_multi_draw_arrays_extension.h"
// #include "IMAGE.h"
// #include "jpeg.h"
#include "./maths/Maths.h"
#include "BSP.h"

// extern LOG errorLog;


////////////////////BSP::Load///////////////
////////////////////////////////////////////
bool BSP::Load(char * filename, int curveTesselation)
{
	FILE * file;

	file=fopen(filename, "rb");
	if (!file)
	{
		// errorLog.OutputError("Unable to open %s", filename);
		return false;
	}

	//read in header
	fread(&header, sizeof(BSP_HEADER), 1, file);

	//check header data is correct
	if (	header.string[0]!='I' || header.string[1]!='B' ||
		header.string[2]!='S' || header.string[3]!='P' ||
		header.version  !=0x2E )
	{
		// errorLog.OutputError("%s is not a version 0x2E .bsp map file", filename);
		return false;
	}


	//Load in vertices
	if (!LoadVertices(file))
		return false;


	//Load in mesh indices
	//Calculate number of indices
	int numMeshIndices=header.directoryEntries[bspMeshIndices].length/sizeof(int);

	//Create space
	meshIndices=new int[numMeshIndices];
	if (!meshIndices)
	{
		// errorLog.OutputError("Unable to allocate memory for %d mesh indices", numMeshIndices);
		return false;
	}

	//read in the mesh indices
	fseek(file, header.directoryEntries[bspMeshIndices].offset, SEEK_SET);
	fread(meshIndices, header.directoryEntries[bspMeshIndices].length, 1, file);

	

	//Load in faces
	if (!LoadFaces(file, curveTesselation))
		return false;

	
	//Load textures
	// if (!LoadTextures(file)) // #TODO
		// return false; // #TODO

		
	//Load Lightmaps
	// if (!LoadLightmaps(file)) // #TODO
		// return false; // #TODO


	//Load BSP Data
	if (!LoadBSPData(file))
		return false;


	//Load in entity string
	entityString=new char[header.directoryEntries[bspEntities].length];
	if (!entityString)
	{
		// errorLog.OutputError(	"Unable to allocate memory for %d length entity string",
		// 						header.directoryEntries[bspEntities].length);
		return false;
	}

	//Go to entity string in file
	fseek(file, header.directoryEntries[bspEntities].offset, SEEK_SET);
	fread(entityString, 1, header.directoryEntries[bspEntities].length, file);

	//Output the entity string
	//errorLog.OutputSuccess("Entity String: %s", entityString);


	fclose(file);

	// errorLog.OutputSuccess("%s Loaded successfully", filename);

	return true;
}



///////////////////BSP::LoadVertices////////
////////////////////////////////////////////
bool BSP::LoadVertices(FILE * file)
{
	//calculate number of vertices
	numVertices=header.directoryEntries[bspVertices].length/sizeof(BSP_LOAD_VERTEX);

	//Create space for this many BSP_LOAD_VERTICES
	BSP_LOAD_VERTEX * loadVertices=new BSP_LOAD_VERTEX[numVertices];
	if (!loadVertices)
	{
		// errorLog.OutputError("Unable to allocate memory for %d BSP_LOAD_VERTEXes", numVertices);
		return false;
	}

	//go to vertices in file
	fseek(file, header.directoryEntries[bspVertices].offset, SEEK_SET);

	//read in the vertices
	fread(loadVertices, header.directoryEntries[bspVertices].length, 1, file);

	//Convert to BSP_VERTEXes
	vertices=new BSP_VERTEX[numVertices];
	if (!vertices)
	{
		// errorLog.OutputError("Unable to allocate memory for vertices");
		return false;
	}

	for (int i=0; i<numVertices; ++i)
	{
		//swap y and z and negate z
		vertices[i].position.x=loadVertices[i].position.x;
		vertices[i].position.y=loadVertices[i].position.z;
		vertices[i].position.z=-loadVertices[i].position.y;

		//scale down
		vertices[i].position/=64;

		//Transfer texture coordinates (Invert t)
		vertices[i].decalS=loadVertices[i].decalS;
		vertices[i].decalT=-loadVertices[i].decalT;

		//Transfer lightmap coordinates
		vertices[i].lightmapS=loadVertices[i].lightmapS;
		vertices[i].lightmapT=loadVertices[i].lightmapT;
	}

	if (loadVertices)
		delete [] loadVertices;
	loadVertices=NULL;

	return true;
}

///////////////////BSP::LoadFaces///////////
////////////////////////////////////////////
bool BSP::LoadFaces(FILE * file, int curveTesselation)
{
	//calculate number of load faces
	numTotalFaces=header.directoryEntries[bspFaces].length/sizeof(BSP_LOAD_FACE);

	//Create space for this many BSP_LOAD_FACES
	BSP_LOAD_FACE * loadFaces=new BSP_LOAD_FACE[numTotalFaces];
	if (!loadFaces)
	{
		// errorLog.OutputError("Unable to allocate memory for %d BSP_LOAD_FACEs", numTotalFaces);
		return false;
	}

	//go to faces in file
	fseek(file, header.directoryEntries[bspFaces].offset, SEEK_SET);

	//read in the faces
	fread(loadFaces, header.directoryEntries[bspFaces].length, 1, file);


	//Create space for face directory
	faceDirectory=new BSP_FACE_DIRECTORY_ENTRY[numTotalFaces];
	if (!faceDirectory)
	{
		// errorLog.OutputError(	"Unable to allocate space for face directory with %d entries",
		// 						numTotalFaces);
		return false;
	}
	
	//Clear the face directory
	memset(faceDirectory, 0, numTotalFaces*sizeof(BSP_FACE_DIRECTORY_ENTRY));

	//Init the "faces drawn" bitset
	facesToDraw.Init(numTotalFaces);


	//Calculate how many of each face type there is
	for (int i=0; i<numTotalFaces; ++i)
	{
		if (loadFaces[i].type==bspPolygonFace)
			++numPolygonFaces;
		if (loadFaces[i].type==bspPatch)
			++numPatches;
		if (loadFaces[i].type==bspMeshFace)
			++numMeshFaces;
	}



	//Create space for BSP_POLYGON_FACEs
	polygonFaces=new BSP_POLYGON_FACE[numPolygonFaces];
	if (!polygonFaces)
	{
		// errorLog.OutputError("Unable To Allocate memory for BSP_POLYGON_FACEs");
		return false;
	}

	int currentFace=0;
	//convert loadFaces to polygonFaces
	for (int i=0; i<numTotalFaces; ++i)
	{
		if (loadFaces[i].type!=bspPolygonFace)		//skip this loadFace if it is not a polygon face
			continue;

		polygonFaces[currentFace].firstVertexIndex=loadFaces[i].firstVertexIndex;
		polygonFaces[currentFace].numVertices=loadFaces[i].numVertices;
		polygonFaces[currentFace].textureIndex=loadFaces[i].texture;
		polygonFaces[currentFace].lightmapIndex=loadFaces[i].lightmapIndex;

		//fill in this entry on the face directory
		faceDirectory[i].faceType=bspPolygonFace;
		faceDirectory[i].typeFaceNumber=currentFace;

		++currentFace;
	}



	//Create space for BSP_MESH_FACEs
	meshFaces=new BSP_MESH_FACE[numMeshFaces];
	if (!meshFaces)
	{
		// errorLog.OutputError("Unable To Allocate memory for BSP_MESH_FACEs");
		return false;
	}

	int currentMeshFace=0;
	//convert loadFaces to faces
	for (int i=0; i<numTotalFaces; ++i)
	{
		if (loadFaces[i].type!=bspMeshFace)		//skip this loadFace if it is not a mesh face
			continue;

		meshFaces[currentMeshFace].firstVertexIndex=loadFaces[i].firstVertexIndex;
		meshFaces[currentMeshFace].numVertices=loadFaces[i].numVertices;
		meshFaces[currentMeshFace].textureIndex=loadFaces[i].texture;
		meshFaces[currentMeshFace].lightmapIndex=loadFaces[i].lightmapIndex;
		meshFaces[currentMeshFace].firstMeshIndex=loadFaces[i].firstMeshIndex;
		meshFaces[currentMeshFace].numMeshIndices=loadFaces[i].numMeshIndices;

		//fill in this entry on the face directory
		faceDirectory[i].faceType=bspMeshFace;
		faceDirectory[i].typeFaceNumber=currentMeshFace;

		++currentMeshFace;
	}
	



	//Create space for BSP_PATCHes
	patches=new BSP_PATCH[numPatches];
	if (!patches)
	{
		// errorLog.OutputError("Unable To Allocate memory for BSP_PATCHes");
		return false;
	}

	int currentPatch=0;
	//convert loadFaces to patches
	for (int i=0; i<numTotalFaces; ++i)
	{
		if (loadFaces[i].type!=bspPatch)		//skip this loadFace if it is not a patch
			continue;

		patches[currentPatch].textureIndex=loadFaces[i].texture;
		patches[currentPatch].lightmapIndex=loadFaces[i].lightmapIndex;
		patches[currentPatch].width=loadFaces[i].patchSize[0];
		patches[currentPatch].height=loadFaces[i].patchSize[1];
		
		//fill in this entry on the face directory
		faceDirectory[i].faceType=bspPatch;
		faceDirectory[i].typeFaceNumber=currentPatch;

		//Create space to hold quadratic patches
		int numPatchesWide=(patches[currentPatch].width-1)/2;
		int numPatchesHigh=(patches[currentPatch].height-1)/2;

		patches[currentPatch].numQuadraticPatches=	numPatchesWide*numPatchesHigh;
		patches[currentPatch].quadraticPatches=new BSP_BIQUADRATIC_PATCH
													[patches[currentPatch].numQuadraticPatches];
		if (!patches[currentPatch].quadraticPatches)
		{
			// errorLog.OutputError(	"Unable to allocate memory for %d quadratic patches",
			// 						patches[currentPatch].numQuadraticPatches);
			return false;
		}

		//fill in the quadratic patches
		for (int y=0; y<numPatchesHigh; ++y)
		{
			for (int x=0; x<numPatchesWide; ++x)
			{
				for (int row=0; row<3; ++row)
				{
					for (int point=0; point<3; ++point)
					{
						patches[currentPatch].quadraticPatches[y*numPatchesWide+x].
							controlPoints[row*3+point]=vertices[loadFaces[i].firstVertexIndex+
								(y*2*patches[currentPatch].width+x*2)+
									row*patches[currentPatch].width+point];
					}
				}

				//tesselate the patch
				patches[currentPatch].quadraticPatches[y*numPatchesWide+x].Tesselate(curveTesselation);
			}
		}


		++currentPatch;
	}

	if (loadFaces)
		delete [] loadFaces;
	loadFaces=NULL;

	return true;
}

///////////////////BSP::LoadTextures////////
////////////////////////////////////////////
// bool BSP::LoadTextures(FILE * file)
// {
// 	//Calculate number of textures
// 	numTextures=header.directoryEntries[bspTextures].length/sizeof(BSP_LOAD_TEXTURE);

// 	//Create space for this many BSP_LOAD_TEXTUREs
// 	BSP_LOAD_TEXTURE * loadTextures=new BSP_LOAD_TEXTURE[numTextures];
// 	if (!loadTextures)
// 	{
// 		// errorLog.OutputError("Unable to allocate space for %d BSP_LOAD_TEXTUREs", numTextures);
// 		return false;
// 	}

// 	//Load textures
// 	fseek(file, header.directoryEntries[bspTextures].offset, SEEK_SET);
// 	fread(loadTextures, 1, header.directoryEntries[bspTextures].length, file);

// 	//Create storage space for that many texture identifiers
// 	decalTextures=new GLuint[numTextures];
// 	if (!decalTextures)
// 	{
// 		// errorLog.OutputError("Unable to create storage space for %d texture IDs", numTextures);
// 		return false;
// 	}
	
// 	//Create storage space for that many booleans to tell if texture has loaded
// 	isTextureLoaded=new bool[numTextures];
// 	if (!isTextureLoaded)
// 	{
// 		// errorLog.OutputError("Unable to create storage space for %d booleans", numTextures);
// 		return false;
// 	}
	

// 	//Generate the texture identifiers
// 	glGenTextures(numTextures, decalTextures);

// 	//Loop through and create textures
// 	// IMAGE textureImage;				//Image used to load textures

// 	for (int i=0; i<numTextures; ++i)
// 	{
// 		glBindTexture(GL_TEXTURE_2D, decalTextures[i]);
		
// 		//add file extension to the name
// 		char tgaExtendedName[68];
// 		char jpgExtendedName[68];
// 		strcpy(tgaExtendedName, loadTextures[i].name);
// 		strcat(tgaExtendedName, ".tga");
// 		strcpy(jpgExtendedName, loadTextures[i].name);
// 		strcat(jpgExtendedName, ".jpg");
		
// 		//Load texture image
// 		bool isJpgTexture=false;				//have we loaded a jpg?
// 		if (!textureImage.Load(tgaExtendedName))	//try to load .tga, if not
// 		{
// 			if (LoadJPG(&textureImage, jpgExtendedName))	//try to load jpg
// 			{
// 				isJpgTexture=true;
// 				isTextureLoaded[i]=true;
// 			}
// 			else
// 				isTextureLoaded[i]=false;
// 		}
// 		else
// 			isTextureLoaded[i]=true;
		
// 		//if a jpg texture, need to set UNPACK_ALIGNMENT to 1
// 		if (isJpgTexture)
// 			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

// 		//Create texture
// 		gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA8, textureImage.width, textureImage.height,
// 							textureImage.format, GL_UNSIGNED_BYTE, textureImage.data);

// 		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

// 		//Set Parameters
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	}

// 	if (loadTextures)
// 		delete [] loadTextures;
// 	loadTextures=NULL;

// 	return true;
// }

///////////////////BSP::LoadLightmaps///////
////////////////////////////////////////////
// bool BSP::LoadLightmaps(FILE * file)
// {
// 	//Calculate number of lightmaps
// 	numLightmaps=header.directoryEntries[bspLightmaps].length/sizeof(BSP_LOAD_LIGHTMAP);

// 	//Create space for this many BSP_LOAD_LIGHTMAPs
// 	BSP_LOAD_LIGHTMAP * loadLightmaps=new BSP_LOAD_LIGHTMAP[numLightmaps];
// 	if (!loadLightmaps)
// 	{
// 		errorLog.OutputError("Unable to allocate space for %d BSP_LOAD_LIGHTMAPs", numLightmaps);
// 		return false;
// 	}

// 	//Load textures
// 	fseek(file, header.directoryEntries[bspLightmaps].offset, SEEK_SET);
// 	fread(loadLightmaps, 1, header.directoryEntries[bspLightmaps].length, file);

// 	//Create storage space for that many texture identifiers
// 	lightmapTextures=new GLuint[numLightmaps];
// 	if (!lightmapTextures)
// 	{
// 		errorLog.OutputError("Unable to create storage space for %d texture IDs", numLightmaps);
// 		return false;
// 	}
	
// 	//Generate the texture identifiers
// 	glGenTextures(numLightmaps, lightmapTextures);

// 	//Change the gamma settings on the lightmaps (make them brighter)
// 	float gamma=2.5f;
// 	for (int i=0; i<numLightmaps; ++i)
// 	{
// 		for (int j=0; j<128*128; ++j)
// 		{
// 			float r, g, b;
// 			r=loadLightmaps[i].lightmapData[j*3+0];
// 			g=loadLightmaps[i].lightmapData[j*3+1];
// 			b=loadLightmaps[i].lightmapData[j*3+2];

// 			r*=gamma/255.0f;
// 			g*=gamma/255.0f;
// 			b*=gamma/255.0f;

// 			//find the value to scale back up
// 			float scale=1.0f;
// 			float temp;
// 			if (r > 1.0f && (temp = (1.0f/r)) < scale) scale=temp;
// 			if (g > 1.0f && (temp = (1.0f/g)) < scale) scale=temp;
// 			if (b > 1.0f && (temp = (1.0f/b)) < scale) scale=temp;

// 			// scale up color values
// 			scale*=255.0f;		
// 			r*=scale;
// 			g*=scale;
// 			b*=scale;

// 			//fill data back in
// 			loadLightmaps[i].lightmapData[j*3+0]=(GLubyte)r;
// 			loadLightmaps[i].lightmapData[j*3+1]=(GLubyte)g;
// 			loadLightmaps[i].lightmapData[j*3+2]=(GLubyte)b;
// 		}
// 	}

// 	for (int i=0; i<numLightmaps; ++i)
// 	{
// 		glBindTexture(GL_TEXTURE_2D, lightmapTextures[i]);
		
// 		//Create texture
// 		gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA8, 128, 128,
// 							GL_RGB, GL_UNSIGNED_BYTE, loadLightmaps[i].lightmapData);

// 		//Set Parameters
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	}

// 	//Create white texture for if no lightmap specified
// 	glGenTextures(1, &whiteTexture);
// 	glBindTexture(GL_TEXTURE_2D, whiteTexture);
// 	//Create texture
// 	gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA8, 1, 1,
// 						GL_RGB, GL_FLOAT, white);
// 	//Set Parameters
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

// 	if (loadLightmaps)
// 		delete [] loadLightmaps;
// 	loadLightmaps=NULL;

// 	return true;
// }

///////////////////BSP::LoadBSPData/////////
////////////////////////////////////////////
bool BSP::LoadBSPData(FILE * file)
{
	//Load leaves
	//Calculate number of leaves
	numLeaves=header.directoryEntries[bspLeaves].length/sizeof(BSP_LOAD_LEAF);

	//Create space for this many BSP_LOAD_LEAFS
	BSP_LOAD_LEAF * loadLeaves=new BSP_LOAD_LEAF[numLeaves];
	if (!loadLeaves)
	{
		// errorLog.OutputError("Unable to allocate space for %d BSP_LOAD_LEAFs", numLeaves);
		return false;
	}

	//Create space for this many BSP_LEAFs
	leaves=new BSP_LEAF[numLeaves];
	if (!leaves)
	{
		// errorLog.OutputError("Unable to allocate space for %d BSP_LEAFs", numLeaves);
		return false;
	}

	//Load leaves
	fseek(file, header.directoryEntries[bspLeaves].offset, SEEK_SET);
	fread(loadLeaves, 1, header.directoryEntries[bspLeaves].length, file);

	//Convert the load leaves to leaves
	for (int i=0; i<numLeaves; ++i)
	{
		leaves[i].cluster=loadLeaves[i].cluster;
		leaves[i].firstLeafFace=loadLeaves[i].firstLeafFace;
		leaves[i].numFaces=loadLeaves[i].numFaces;

		//Create the bounding box
		leaves[i].boundingBoxVertices[0].Set((float)loadLeaves[i].mins[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].mins[1]);
		leaves[i].boundingBoxVertices[1].Set((float)loadLeaves[i].mins[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].maxs[1]);
		leaves[i].boundingBoxVertices[2].Set((float)loadLeaves[i].mins[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].mins[1]);
		leaves[i].boundingBoxVertices[3].Set((float)loadLeaves[i].mins[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].maxs[1]);
		leaves[i].boundingBoxVertices[4].Set((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].mins[1]);
		leaves[i].boundingBoxVertices[5].Set((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].maxs[1]);
		leaves[i].boundingBoxVertices[6].Set((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].mins[1]);
		leaves[i].boundingBoxVertices[7].Set((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].maxs[1]);

		for (int j=0; j<8; ++j)
			leaves[i].boundingBoxVertices[j]/=64;
	}

	
	
	//Load leaf faces array
	int numLeafFaces=header.directoryEntries[bspLeafFaces].length/sizeof(int);

	//Create space for this many leaf faces
	leafFaces=new int[numLeafFaces];
	if (!leafFaces)
	{
		// errorLog.OutputError("Unable to allocate space for %d leaf faces", numLeafFaces);
		return false;
	}

	//Load leaf faces
	fseek(file, header.directoryEntries[bspLeafFaces].offset, SEEK_SET);
	fread(leafFaces, 1, header.directoryEntries[bspLeafFaces].length, file);


	
	//Load Planes
	numPlanes=header.directoryEntries[bspPlanes].length/sizeof(PLANE);

	//Create space for this many planes
	planes=new PLANE[numPlanes];
	if (!planes)
	{
		// errorLog.OutputError("Unable to allocate space for %d planes", numPlanes);
		return false;
	}

	fseek(file, header.directoryEntries[bspPlanes].offset, SEEK_SET);
	fread(planes, 1, header.directoryEntries[bspPlanes].length, file);

	//reverse the intercept on the planes and convert planes to OGL coordinates
	for (int i=0; i<numPlanes; ++i)
	{
		//swap y and z and negate z
		float temp=planes[i].normal.y;
		planes[i].normal.y=planes[i].normal.z;
		planes[i].normal.z=-temp;

		planes[i].intercept=-planes[i].intercept;
		planes[i].intercept/=64;	//scale down
	}




	//Load nodes
	numNodes=header.directoryEntries[bspNodes].length/sizeof(BSP_NODE);

	//Create space for this many nodes
	nodes=new BSP_NODE[numNodes];
	if (!nodes)
	{
		// errorLog.OutputError("Unable to allocate space for %d nodes", numNodes);
		return false;
	}

	fseek(file, header.directoryEntries[bspNodes].offset, SEEK_SET);
	fread(nodes, 1, header.directoryEntries[bspNodes].length, file);





	//Load visibility data
	//load numClusters and bytesPerCluster
	fseek(file, header.directoryEntries[bspVisData].offset, SEEK_SET);
	fread(&visibilityData, 2, sizeof(int), file);

	//Calculate the size of the bitset
	int bitsetSize=visibilityData.numClusters*visibilityData.bytesPerCluster;

	//Create space for bitset
	visibilityData.bitset=new GLubyte[bitsetSize];
	if (!visibilityData.bitset)
	{
		// errorLog.OutputError(	"Unable to allocate memory for visibility bitset of size %d bytes",
		// 						bitsetSize);
		return false;
	}
	//read bitset
	fread(visibilityData.bitset, 1, bitsetSize, file);

	if (loadLeaves)
		delete [] loadLeaves;
	loadLeaves=NULL;


	return true;
}







//BSP Functions
//calculate which leaf the camera lies in
int BSP::CalculateCameraLeaf(const VECTOR3D & cameraPosition)
{
	int currentNode=0;
	
	//loop until we find a negative index
	while(currentNode>=0)
	{
		//if the camera is in front of the plane for this node, assign i to be the front node
		// if (planes[nodes[currentNode].planeIndex].ClassifyPoint(cameraPosition)==POINT_IN_FRONT_OF_PLANE)
			currentNode=nodes[currentNode].front;
		// else
			// currentNode=nodes[currentNode].back;
	}

	//return leaf index
	return ~currentNode;
}

//See if one cluster is visible from another
int BSP::isClusterVisible(int cameraCluster, int testCluster)
{
	int index=	cameraCluster*visibilityData.bytesPerCluster + testCluster/8;

	int returnValue=visibilityData.bitset[index] & (1<<(testCluster & 7));

	return returnValue;
}

//Calculate which faces to draw given a position & frustum
void BSP::CalculateVisibleFaces(const VECTOR3D & cameraPosition/*, FRUSTUM frustum*/)
{
	//Clear the list of faces drawn
	facesToDraw.ClearAll();
	
	//calculate the camera leaf
	int cameraLeaf=CalculateCameraLeaf(cameraPosition);
	int cameraCluster=leaves[cameraLeaf].cluster;

	//loop through the leaves
	for (int i=0; i<numLeaves; ++i)
	{
		//if the leaf is not in the PVS, continue
		if (!isClusterVisible(cameraCluster, leaves[i].cluster))
			continue;

		//if this leaf does not lie in the frustum, continue
		// if (!frustum.IsBoundingBoxInside(leaves[i].boundingBoxVertices)) // #TODO
		// 	continue;

		//loop through faces in this leaf and mark them to be drawn
		for (int j=0; j<leaves[i].numFaces; ++j)
		{
			facesToDraw.Set(leafFaces[leaves[i].firstLeafFace+j]);
		}
	}

	
}










//DRAWING FUNCTIONS
//Draw all faces marked as visible
void BSP::Draw()
{
	glFrontFace(GL_CW);

	//enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	// glEnableClientState(GL_TEXTURE_COORD_ARRAY); // #TODO

	// glClientActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// glEnableClientState(GL_TEXTURE_COORD_ARRAY); // #TODO
	// glClientActiveTextureARB(GL_TEXTURE0_ARB); // #TODO

	//loop through faces
	for (int i=0; i<numTotalFaces; ++i)
	{
		//if this face is to be drawn, draw it
		if (facesToDraw.IsSet(i))
			DrawFace(i);
	}
	
	//disable vertex arrays
	// glClientActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// glDisableClientState(GL_TEXTURE_COORD_ARRAY); // #TODO
	// glClientActiveTextureARB(GL_TEXTURE0_ARB); // #TODO

	// glDisableClientState(GL_TEXTURE_COORD_ARRAY); // #TODO
	glDisableClientState(GL_VERTEX_ARRAY);

	glFrontFace(GL_CCW);
}


//Draw a face
void BSP::DrawFace(int faceNumber)
{
	//look this face up in the face directory
	if (faceDirectory[faceNumber].faceType==0)
		return;
	
	if (faceDirectory[faceNumber].faceType==bspPolygonFace)
		DrawPolygonFace(faceDirectory[faceNumber].typeFaceNumber);

	if (faceDirectory[faceNumber].faceType==bspMeshFace)
		DrawMeshFace(faceDirectory[faceNumber].typeFaceNumber);

	if (faceDirectory[faceNumber].faceType==bspPatch)
		DrawPatch(faceDirectory[faceNumber].typeFaceNumber);
}


//Draw a polygon face
void BSP::DrawPolygonFace(int polygonFaceNumber)
{
	//skip this face if its texture was not loaded
	// if (isTextureLoaded[polygonFaces[polygonFaceNumber].textureIndex]==false) // #TODO
		// return; // #TODO

	//set array pointers
	glVertexPointer(	3, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[0].position);
	
	//Unit 0 - decal textures
	// glTexCoordPointer(	2, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[0].decalS); // #TODO
	
	//Unit 1 - Lightmaps
	// glClientActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// glTexCoordPointer(2, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[0].lightmapS); // #TODO
	// glClientActiveTextureARB(GL_TEXTURE0_ARB); // #TODO
	

	//bind textures
	//unit 0 - decal texture
	// glBindTexture(GL_TEXTURE_2D, decalTextures[polygonFaces[polygonFaceNumber].textureIndex]); // #TODO

	//unit 1 - lightmap
	// glActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// if (polygonFaces[polygonFaceNumber].lightmapIndex>=0)	//only bind a lightmap if one exists // #TODO
		// glBindTexture(	GL_TEXTURE_2D, lightmapTextures[polygonFaces[polygonFaceNumber].lightmapIndex]); // #TODO
	// else // #TODO
		// glBindTexture(GL_TEXTURE_2D, whiteTexture); // #TODO
	// glActiveTextureARB(GL_TEXTURE0_ARB); // #TODO

	//Draw face
	glDrawArrays(	GL_TRIANGLE_FAN, polygonFaces[polygonFaceNumber].firstVertexIndex, polygonFaces[polygonFaceNumber].numVertices);
}

//Draw a mesh face
void BSP::DrawMeshFace(int meshFaceNumber)
{
	//skip this face if its texture was not loaded
	// if (isTextureLoaded[meshFaces[meshFaceNumber].textureIndex]==false) // #TODO
		// return; // #TODO

	//set array pointers
	glVertexPointer(	3, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[meshFaces[meshFaceNumber].firstVertexIndex].position);
	// glTexCoordPointer(	2, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[meshFaces[meshFaceNumber].firstVertexIndex].decalS); // #TODO

	// glClientActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// glTexCoordPointer(	2, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[meshFaces[meshFaceNumber].firstVertexIndex].lightmapS); // #TODO
	// glClientActiveTextureARB(GL_TEXTURE0_ARB); // #TODO


	//bind textures
	//unit 0 - decal texture
	// glBindTexture(GL_TEXTURE_2D, decalTextures[meshFaces[meshFaceNumber].textureIndex]); // #TODO

	//unit 1 - lightmap
	// glActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// if (meshFaces[meshFaceNumber].lightmapIndex>=0)	//only bind a lightmap if one exists // #TODO
		// glBindTexture(GL_TEXTURE_2D, lightmapTextures[meshFaces[meshFaceNumber].lightmapIndex]); // #TODO
	// else // #TODO
		// glBindTexture(GL_TEXTURE_2D, whiteTexture); // #TODO
	// glActiveTextureARB(GL_TEXTURE0_ARB); // #TODO


	//draw the face, using meshIndices
	// if (!EXT_draw_range_elements_supported) // #TODO
	// { // #TODO
		glDrawElements(	GL_TRIANGLES, meshFaces[meshFaceNumber].numMeshIndices, GL_UNSIGNED_INT,
						&meshIndices[meshFaces[meshFaceNumber].firstMeshIndex]);
	// } // #TODO
	// else // #TODO
	// { // #TODO
		// glDrawRangeElementsEXT(	GL_TRIANGLES, 0, meshFaces[meshFaceNumber].numVertices, meshFaces[meshFaceNumber].numMeshIndices, GL_UNSIGNED_INT, &meshIndices[meshFaces[meshFaceNumber].firstMeshIndex]); // #TODO
	// } // #TODO
}

//Draw a patch
void BSP::DrawPatch(int patchNumber)
{
	//skip this patch if its texture was not loaded
	// if (isTextureLoaded[patches[patchNumber].textureIndex]==false) // #TODO
		// return; // #TODO

	//bind textures
	//unit 0 - decal texture
	// glBindTexture(GL_TEXTURE_2D, decalTextures[patches[patchNumber].textureIndex]); // #TODO

	//unit 1 - lightmap
	// glActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// if (patches[patchNumber].lightmapIndex>=0)	//only bind a lightmap if one exists // #TODO
		// glBindTexture(GL_TEXTURE_2D, lightmapTextures[patches[patchNumber].lightmapIndex]); // #TODO
	// else // #TODO
		// glBindTexture(GL_TEXTURE_2D, whiteTexture); // #TODO
	// glActiveTextureARB(GL_TEXTURE0_ARB); // #TODO

	for (int i=0; i<patches[patchNumber].numQuadraticPatches; ++i)
		patches[patchNumber].quadraticPatches[i].Draw();
}


//Tesselate a biquadratic patch
bool BSP_BIQUADRATIC_PATCH::Tesselate(int newTesselation)
{
	tesselation=newTesselation;

	float px, py;
	BSP_VERTEX temp[3];
	vertices=new BSP_VERTEX[(tesselation+1)*(tesselation+1)];

	for (int v=0; v<=tesselation; ++v)
	{
		px=(float)v/tesselation;

		vertices[v]=controlPoints[0]*((1.0f-px)*(1.0f-px))+
					controlPoints[3]*((1.0f-px)*px*2)+
					controlPoints[6]*(px*px);
	}

	for (int u=1; u<=tesselation; ++u)
	{
		py=(float)u/tesselation;

		temp[0]=controlPoints[0]*((1.0f-py)*(1.0f-py))+
				controlPoints[1]*((1.0f-py)*py*2)+
				controlPoints[2]*(py*py);

		temp[1]=controlPoints[3]*((1.0f-py)*(1.0f-py))+
				controlPoints[4]*((1.0f-py)*py*2)+
				controlPoints[5]*(py*py);

		temp[2]=controlPoints[6]*((1.0f-py)*(1.0f-py))+
				controlPoints[7]*((1.0f-py)*py*2)+
				controlPoints[8]*(py*py);

		for (int v=0; v<=tesselation; ++v)
		{
			px=(float)v/tesselation;

			vertices[u*(tesselation+1)+v]=	temp[0]*((1.0f-px)*(1.0f-px))+
											temp[1]*((1.0f-px)*px*2)+
											temp[2]*(px*px);
		}
	}

	//Create indices
	indices=new GLuint[tesselation*(tesselation+1)*2];
	if (!indices)
	{
		// errorLog.OutputError("Unable to allocate memory for surface indices");
		return false;
	}

	for (int row=0; row<tesselation; ++row)
	{
		for (int point=0; point<=tesselation; ++point)
		{
			//calculate indices
			//reverse them to reverse winding
			indices[(row*(tesselation+1)+point)*2+1]=row*(tesselation+1)+point;
			indices[(row*(tesselation+1)+point)*2]=(row+1)*(tesselation+1)+point;
		}
	}


	//Fill in the arrays for multi_draw_arrays
	trianglesPerRow=new int[tesselation];
	rowIndexPointers=new unsigned int *[tesselation];
	if (!trianglesPerRow || !rowIndexPointers)
	{
		// errorLog.OutputError("Unable to allocate memory for indices for multi_draw_arrays");
		return false;
	}

	for (int row=0; row<tesselation; ++row)
	{
		trianglesPerRow[row]=2*(tesselation+1);
		rowIndexPointers[row]=&indices[row*2*(tesselation+1)];
	}

	return true;
}


//Draw a biquadratic patch
void BSP_BIQUADRATIC_PATCH::Draw()
{
	//set array pointers
	glVertexPointer(3, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[0].position);
		
	// glTexCoordPointer(2, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[0].decalS); // #TODO
	
	// glClientActiveTextureARB(GL_TEXTURE1_ARB); // #TODO
	// glTexCoordPointer(2, GL_FLOAT, sizeof(BSP_VERTEX), &vertices[0].lightmapS); // #TODO
	// glClientActiveTextureARB(GL_TEXTURE0_ARB); // #TODO
	
	//Draw a triangle strip for each row
	// if (!EXT_multi_draw_arrays_supported) // #TODO
	// { // #TODO
		for (int row=0; row<tesselation; ++row)
		{
			glDrawElements(	GL_TRIANGLE_STRIP, 2*(tesselation+1), GL_UNSIGNED_INT,
							&indices[row*2*(tesselation+1)]);
		}
	// } else { // #TODO
		// glMultiDrawElementsEXT(	GL_TRIANGLE_STRIP, trianglesPerRow, GL_UNSIGNED_INT, (const void **)rowIndexPointers, tesselation); // #TODO
	// }							 // #TODO
}



