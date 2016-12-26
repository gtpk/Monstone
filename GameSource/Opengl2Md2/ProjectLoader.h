#include <string>


using std::string;

class ProjectLoader
{

	static ProjectLoader* instance;
private :
	

	bool isLoaded;
public:
	ProjectLoader();
	~ProjectLoader();
	string ProjectPath;
	string GetProjectPath();
	string GetProjectPath(string path);

	static ProjectLoader* getinstance();
	void SaveProjectFile();

private:

	bool LoadProjectFile(string path);
	

};

