

throw Exception("Session \"" + sessionName + "\" not found!", __FILE__, __LINE__);

try {

}
catch (Exception e)
{
  cerr << "[ERROR]: " << e.getMessage() << '\n';
}
