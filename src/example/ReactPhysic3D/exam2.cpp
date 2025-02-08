/*
 * This is a "hello world" project with a basic example of how to use
 * the ReactPhysics3D library in your project. This example is a simple
 * rigid body that is falling down because of gravity.
 */

// Libraries
#include <reactphysics3d/reactphysics3d.h>
#include <iostream>

// ReactPhysics3D namespace
using namespace reactphysics3d;

// Main function
int main(int argc, char** argv) {

	// First you need to create the PhysicsCommon object. This is a factory module
	// that you can use to create physics world and other objects. It is also responsible
	// for logging and memory management
	PhysicsCommon physicsCommon;

	// Create the world settings
	PhysicsWorld::WorldSettings settings;
	// settings.defaultVelocitySolverNbIterations = 20;
	// settings.isSleepingEnabled = false;
	// settings.gravity = Vector3(0, -9.81, 0);
	settings.gravity = Vector3(0, -1.0, 0);

	// Create a physics world
	PhysicsWorld* world = physicsCommon.createPhysicsWorld(settings);

	// More Setting
	// world->setNbIterationsVelocitySolver(15); // Change the number of iterations of the velocity solver
	// world->setNbIterationsPositionSolver(8); // Change the number of iterations of the position solver
	// world->enableSleeping(false); // Disable the sleeping technique

	// Create a rigid body in the world
	Vector3 position(0, 20, 0);
	Quaternion orientation = Quaternion::identity();
	Transform transform(position, orientation);
	RigidBody* body = world->createRigidBody(transform);

	// Change the type of the body to kinematic
	// body->setType(BodyType::KINEMATIC);

	// Disable gravity for this body
	// rigidBody->enableGravity(false);

	// Giảm tốc độ
	// RigidBody::setLinearDamping()
	// RigidBody::setAngularDamping()

	// Ko cho phép sleep
	// body->setIsAllowedToSleep(false);

	// Áp dụng lực
	// Vector3 force(2.0, 0.0, 0.0);
	// body->applyForceToCenterOfMass(Vector3(2.0, 0.0, 0.0));

	// Áp dụng lực tại điểm
	// Vector3 force(2.0, 0.0, 0.0);
	// Vector3 point(4.0, 5.0, 6.0);
	// body->applyForceAtWorldPosition(force, point); // Trong thế giới
	// body->applyForceAtLocalPosition(force, point); // Nội suy từ chính vật

	// Áp dụng mô men xoắn
	// Vector3 torque(0.0, 3.0, 0.0);
	// rigidBody->applyTorque(torque);

	// Get Tranform
	// RigidBody::getTransform()
	// Hoặc cho OpenGL
	// float matrix[16];
	// transform.getOpenGLMatrix(matrix);

	// Mass
	// RigidBody::setMass()
	// RigidBody::updateMassFromColliders()

	// Trọng tâm khối lượng
	// RigidBody::setLocalCenterOfMass()
	// RigidBody::updateLocalCenterOfMassFromColliders()

	// Quán tính
	// RigidBody::setLocalInertiaTensor()
	// RigidBody::updateLocalInertiaTensorFromColliders()

	// Tính cả Mass và trọng tâm bằng
	// RigidBody::updateMassPropertiesFromColliders()

	// Khóa hướng di chuyển và hướng xoay
	// rigidBody->setLinearAxisFactor(Vector3(1, 0, 1)); // Vô hiệu hóa chuyển động dọc theo trục Y
	// rigidBody->setAngularAxisFactor(Vector3(1, 0, 1)); // Vô hiệu hóa xoay quanh trục Y


	// Bộ va chạm
	// float radius = 3.0f;
	// SphereShape* sphereShape = physicsCommon.createSphereCollisionShape(radius);
	// Transform transform = Transform::identity();
	// Collider* collider = body->addCollider(&shape, transform);

	// Hình hộp
	// const Vector3 halfExtents(2.0, 3.0, 5.0);
	// BoxShape * boxShape = phycsicsCommon.createBoxShape(halfExtents);
	// Hình cầu
	// SphereShape * sphereShape = physicsCommon.createSphereShape ( 2.0 );
	// Tạo hình dạng viên nang
	// CapsuleShape * capsuleShape = physicsCommon.createCapsuleShape (1.0, 2.0);

	// Hình dạng lưới lồi từ các mặt phẳng *********
	// PhysicsCommon::createConvexMesh(const PolygonVertexArray& polygonVertexArray, std::vector<Message>& messages)
	// float vertices[24] = {-3, -3, 3,
  //         3, -3, 3,
  //         3, -3, -3,
  //         -3, -3, -3,
  //         -3, 3, 3,
  //         3, 3, 3,
  //         3, 3, -3,
  //         -3, 3, -3};
	// int indices[24] = {0, 3, 2, 1,
  //                  4, 5, 6, 7,
  //                  0, 1, 5, 4,
  //                  1, 2, 6, 5,
  //                  2, 3, 7, 6,
  //                  0, 4, 7, 3};
	// PolygonVertexArray::PolygonFace* polygonFaces = new PolygonVertexArray::PolygonFace[6];
	// PolygonVertexArray::PolygonFace* face = polygonFaces;
	// for (int f = 0; f < 6; f++) {
	// 		// First vertex of the face in the indices array
	// 		face->indexBase = f * 4;   
	// 		// Number of vertices in the face
	// 		face->nbVertices = 4;
	// 		face++;
	// }
	// PolygonVertexArray* polygonVertexArray = new PolygonVertexArray(8, vertices, 3 * sizeof(float), indices, sizeof(int), 6, polygonFaces,
	// PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
	// PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
	// std::vector<rp3d::Message> messages;
	// ConvexMesh* convexMesh = physicsCommon.createConvexMesh(polygonVertexArray, messages);
	// if (messages.size() > 0) {
	// 	for (const rp3d::Message& message: messages) {
	// 		std::string messageType;
	// 		switch(message.type) {
	// 			case rp3d::Message::Type::Information:
	// 				messageType = "info";
	// 				break;
	// 			case rp3d::Message::Type::Warning:
	// 				messageType = "warning";
	// 				break;
	// 			case rp3d::Message::Type::Error:
	// 				messageType = "error";
	// 				break;
	// 		}
	// 		std::cout << "Message (" << messageType << "): " << message.text << std::endl;
	// 	}
	// }
	// assert(convexMesh != nullptr);

	// Hình dạng lưới lồi từ các điểm *********
	// float vertices[24] = {-3, -3, 3,
	// 				3, -3, 3,
	// 				3, -3, -3,
	// 				-3, -3, -3,
	// 				-3, 3, 3,
	// 				3, 3, 3,
	// 				3, 3, -3,
	// 				-3, 3, -3};
	// rp3d::VertexArray vertexArray(vertices, 3 * sizeof(float), 8, rp3d::VertexArray::DataType::VERTEX_FLOAT_TYPE);
	// std::vector<rp3d::Message> messages;
	// ConvexMesh* convexMesh = physicsCommon.createConvexMesh(vertexArray, messages);

	// Shape từ Mesh
	// Vector3 scaling(1, 1, 1);
	// ConvexMeshShape* convexMeshShape = physicsCommon.createConvexMeshShape(convexMesh, scaling);

	// Hình dạng lưới lõm từ các mặt phẳng *********
	// const int nbVertices = 8;
	// const int nbTriangles = 12;
	// float vertices[3 * nbVertices] = ...;
	// int indices[3 * nbTriangles] = ...;
	// TriangleVertexArray* triangleArray =
	// new TriangleVertexArray(nbVertices, vertices, 3 * sizeof(float), nbTriangles,
	// indices, 3 * sizeof(int),
	// TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
	// TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
	// std::vector<rp3d::Message> messages;
	// TriangleMesh* triangleMesh = physicsCommon.createTriangleMesh(vertexArray, messages);
	// Shape từ Mesh
	// const Vector3 scaling(1, 1, 1);
	// ConcaveMeshShape* concaveMeshShape = physicsCommon.createConcaveMeshShape(triangleMesh, scaling);

	// HeightShape
	// heightValues[indexRow * nbColumns + indexColumn]
	// const int nbRows = 40;
	// const int nbColumns = 50;
	// float minHeight = 100;
	// float maxHeight = 500;
	// float heightValues[nbRows * nbColumns] = ...;
	// std::vector<rp3d::Message> messages;
	// HeightField* heightField = physicsCommon.createHeightField(NB_POINTS_WIDTH, NB_POINTS_LENGTH,
	// 									heightValues, rp3d::HeightField::HeightDataType::HEIGHT_FLOAT_TYPE,
	// 									messages);
	// HeightFieldShape* heightFieldShape = physicsCommon.createHeightFieldShape(heightField);


	// Nhóm tương tác
	// enum Category {
	// 	CATEGORY1 = 0x0001,
	// 	CATEGORY2 = 0x0002,
	// 	CATEGORY3 = 0x0004
	// };
	// colliderBody1->setCollisionCategoryBits(CATEGORY1);
	// colliderBody2->setCollisionCategoryBits(CATEGORY2);
	// colliderBody1->setCollideWithMaskBits(CATEGORY3);
	// colliderBody2->setCollideWithMaskBits(CATEGORY1 | CATEGORY3);
	// Phải 2 chiều mới tưởng tác đc, ví dụ này cả 2 ko tương tác nhau


	// Vật liệu
	// Material& material = collider->getMaterial(); // Lấy vậy liệu
	// material.setBounciness(0.4); // Độ nảy (0 - 1)
	// material.setMassDensity(0.5); // Mật độ khối lượng (0 - 1)
	// material.setFrictionCoefficient(0.2); // Hệ số ma sát


	// Máy va chạm mô phỏng
	// bomCollider->setIsSimulationCollider(true); // thiết lập một bộ va chạm thành bộ va chạm mô phỏng

	// Máy va chạm truy vấn thế giới
	// testOverlap() // Kiểm tra chồng chéo lên nhau ko
	// testCollision() // Điểm chạm và pháp tuyến 2 vật thể
	// testPointInside() // Điểm nằm trong body, Collider ko
	// raycast() // Dò tia
	// bombCollider->setIsWorldQueryCollider( đúng ); // Đặt thành va chạm thế giới

	// Trigger - Cò súng
	// Ví dụ mìn sẽ ko tương tác với xung quanh, chỉ gọi hàm chạm khi chạm với ng chơi
	// bomCollider->setIsTrigger(true);

	// Khớp nối: xem https://www.reactphysics3d.com/documentation/index.html#usingrp3d


	// Dò tia
	// class MyCallbackClass : public RaycastCallback {
	// public:
	// 	virtual decimal notifyRaycastHit(const RaycastInfo& info) {
	// 		RaycastInfo info = {
	// 			worldPoint: Điểm sinh lực trong tọa độ không gian thế giới
	// 			worldNormal: Bề mặt bình thường của máy va chạm tại điểm va chạm trong tọa độ không gian thế giới
	// 			hitFraction: Khoảng cách phân số của điểm trúng đích giữa startPoint và endPoint của tia. Điểm trúng đích p là như vậy$p = startPoint + hitFraction \cdot (endPoint - startPoint)$
	// 			body: Con trỏ đến vật thể cứng đã bị tia chiếu vào
	// 			collide: Con trỏ đến máy va chạm đã bị tia bắn trúng
	// 		}
	// 		std::cout << "Hit point : " <<
	// 			info.worldPoint.x <<
	// 			info.worldPoint.y <<
	// 			info.worldPoint.z <<
	// 			std::endl;
	// 		return decimal(1.0);
	// 	}
	// };
	// Vector3 startPoint(0.0, 5.0, 1.0);
	// Vector3 endPoint(0.0, 5.0, 30);
	// Ray ray(startPoint, endPoint);
	// Kiểm tra trên thể giới
	// MyCallbackClass callbackObject;
	// world->raycast(ray, &callbackObject);
	// Hoặc chỉ kiểm tra đối với đối tượng cụ thể
	// RaycastInfo raycastInfo;
	// bool isHit = body->raycast(ray, raycastInfo);
	// Hoặc chỉ kiểm tra trên 1 bộ phận của body
	// bool isHit = collider->raycast(ray, raycastInfo);


	// Lắng nghe sự kiện
	// class YourEventListener : public EventListener {
	// 	// Phát hiện va chạm, trước khi tương tác
	// 	virtual void onContact(const CollisionCallback::CallbackData& callbackData) overrride {
	// 		ContactPair: {
	// 			getBody1()
	// 			getBody2()
	// 			getCollider1()
	// 			getCollider2()
	// 			getNbContactPoints()
	// 			getContactPoint(): CollisionCallback::ContactPoint
	// 			getEventType(): ContactStart|ContactStay|ContactExit
	// 		}
	// 		for (uint p = 0; p < callbackData.getNbContactPairs(); p++) {
	// 			CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);
	// 			for (uint c = 0; c < contactPair.getNbContactPoints(); c++) {
	// 				CollisionCallback::ContactPoint contactPoint = contactPair.getContactPoint(c);
	// 				Vector3 worldPoint = contactPair.getCollider1()->getLocalToWorldTransform() * contactPoint.getLocalPointOnCollider1();
	// 				// ...
	// 			}
	// 		}
	// 	}
	// 	// Phát hiện va chạm với bộ kích hoạt (Trigger)
	// 	virtual void onTrigger(const OverlapCallback::CallbackData& callbackData) overrride {
	// 		CallbackData: {
	// 			getNbOverlappingPairs()
	// 			getOverlappingPair()
	// 		}
	// 		getEventType(): OverlapStart|OverlapStay|OverlapExit
	// 	}
	// };
	// YourEventListener listener;
	// world->setEventListener(&listener); // Đăng ký sự kiện


	// Log
	// DefaultLogger* logger = physicsCommon.createDefaultLogger();
	// uint logLevel = static_cast<uint>(static_cast<uint>(Logger::Level::Warning) | static_cast<uint>(Logger::Level::Error);
	// logger->addFileDestination("rp3d_log_" + name + ".html", logLevel, DefaultLogger::Format::HTML);
	// logger->addStreamDestination(std::cout, logLevel, DefaultLogger::Format::Text);
	// physicsCommon.setLogger(logger);


	// Debug Render
	// physicsWorld->setIsDebugRenderingEnabled(true);
	// body->setIsDebugEnabled(true);
	// DebugRenderer& debugRenderer = physicsWorld->getDebugRenderer();
	// debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_POINT, true);
	// debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_NORMAL, true);
	// DebugRenderer::getNbLines() // Total Line
	// DebugRenderer::getNbTriangles() // Total Triangle
	// DebugRenderer::getLinesArray() // Pointer First Line
	// DebugRenderer::getTrianglesArray() // Pointer First Triangle


	// Step the simulation a few steps
	const decimal timeStep = 1.0f / 60.0f;
	for (int i=0; i < 20; i++) {

		world->update(timeStep);

		// Get the updated position of the body
		const Transform& transform = body->getTransform();
		const Vector3& position = transform.getPosition();

		// Display the position of the body
		std::cout << "Step: " << i << " | Body Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
	}

	// Destroy a rigid body
	world->destroyRigidBody(body);

	// Destroy a physics world
	physicsCommon.destroyPhysicsWorld(world);

	return 0;
}
