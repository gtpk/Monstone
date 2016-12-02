#include <string>


using std::string;

class ProjectLoader
{


private :
	string ProjectPath; 

	bool isLoaded;
public:
	ProjectLoader();
	~ProjectLoader();

	string GetProjectPath();
	string GetProjectPath(string path);



	static ProjectLoader& getinstance();
	void SaveProjectFile();

private:

	bool LoadProjectFile(string path);
	

};

