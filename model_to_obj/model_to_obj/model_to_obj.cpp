// model_to_obj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>


struct vPosition
{
	float x,y,z;
};

std::string convertWCharArrayToString(const WCHAR * const wcharArray)
{
	std::stringstream ss;
	int i = 0;
	char c = (char) wcharArray[i];
	while(c != '\0')
	{
		ss <<c;
		i++;
		c = (char) wcharArray[i];
	}
	std::string convert = ss.str();
	return convert;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int vertex_Count = 0;

	FILE *objFile;
	objFile = fopen("test.obj", "w");
	if (!objFile)
	{
		return -1;
	}

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile((LPCWSTR)"*", &findFileData);
	if(hFind  == INVALID_HANDLE_VALUE)
	{
		std::cout <<"No files found." <<std::endl;
	} else
	{
		std::cout <<"Files found." <<std::endl;
	}

	int fileNumber = 0;
	int model_number = 0;

	while(FindNextFile(hFind, &findFileData))
	{

		size_t found;
		found=convertWCharArrayToString(findFileData.cFileName).find(".3d");
		if (found!=std::string::npos)
		{
			std::cout << convertWCharArrayToString(findFileData.cFileName) <<std::endl;
			//file found;)

			//read it
			std::vector<vPosition> mVertex;

			FILE *binaryFile;
			binaryFile = fopen (convertWCharArrayToString(findFileData.cFileName).c_str(), "rb");
			if (!binaryFile)
			{
				return -1;
			}

			//one file only
			while(!feof(binaryFile))
			{
				int vertexCount = 0;
				int vertexType = 0;

				int postype = 0;
				int transform2d = 0;

				mVertex.clear();
				
				//
				fread(&vertexCount,sizeof(int),1,binaryFile);
				fread(&vertexType,sizeof(int),1,binaryFile);
				fread(&postype,sizeof(int),1,binaryFile);
				fread(&transform2d,sizeof(int),1,binaryFile);

				
				for(int i = 0; i < vertexCount;i++)
				{
					vPosition mPosition;
					mPosition.x = 0.0f;
					mPosition.y = 0.0f;
					mPosition.z = 0.0f;

					fread(&mPosition.x,sizeof(float),1,binaryFile);
					fread(&mPosition.y,sizeof(float),1,binaryFile);
					fread(&mPosition.z,sizeof(float),1,binaryFile);
					mVertex.push_back(mPosition);

					if (mPosition.x > 100000 || mPosition.x < -100000 || mPosition.y > 100000 || mPosition.y < -100000 || mPosition.z > 100000 || mPosition.z < -100000)
					{
						printf("dupa...\n");
					}
				}
				printf("vc: %d vt: %d vp: %d t2d: %d\n",vertexCount,vertexType,postype,transform2d);

				
				if (transform2d == 0)
				{
					//export
					if (vertexType == 3)//triangle
					{
						model_number++;
						fprintf(objFile,"\n");

						//v - vertex data
						for(int i = 0; i < vertexCount;i++)
						{
							fprintf(objFile,"v %f %f %f\n",mVertex[i].x,mVertex[i].y,mVertex[i].z);
						}

						//g - model name
						fprintf(objFile,"\ng model%d\n",model_number);
						//f - faces
						if (vertex_Count > 0)
						{
							for (int i = 0; i < vertexCount;i+=3)
							{
								fprintf(objFile,"f %d %d %d\n",vertex_Count + i,vertex_Count + i+1,vertex_Count + i+2);
							}
							vertex_Count += vertexCount;
						}else
						{
							for (int i = 1; i < vertexCount+1;i+=3)
							{
								fprintf(objFile,"f %d %d %d\n",vertex_Count + i,vertex_Count + i+1,vertex_Count + i+2);
							}
							vertex_Count += vertexCount+1;
						}
					}else
						if (vertexType == 4)//vertex strip
						{
							model_number++;
							fprintf(objFile,"\n");

							bool flip = false;
							int stripcount = 0;
							//v - vertex data
							for(int i = 0; i < vertexCount;i++)
							{
								if(i > 2)
								{
									if(flip)
									{
										fprintf(objFile,"v %f %f %f\n",mVertex[i-2].x,mVertex[i-2].y,mVertex[i-2].z);
										fprintf(objFile,"v %f %f %f\n",mVertex[i-1].x,mVertex[i-1].y,mVertex[i-1].z);
										fprintf(objFile,"v %f %f %f\n",mVertex[i].x,mVertex[i].y,mVertex[i].z);
									}else
									{
										fprintf(objFile,"v %f %f %f\n",mVertex[i].x,mVertex[i].y,mVertex[i].z);
										fprintf(objFile,"v %f %f %f\n",mVertex[i-1].x,mVertex[i-1].y,mVertex[i-1].z);
										fprintf(objFile,"v %f %f %f\n",mVertex[i-2].x,mVertex[i-2].y,mVertex[i-2].z);
									}
									
									stripcount+=3;
									flip=!flip;
								}else
								{
									fprintf(objFile,"v %f %f %f\n",mVertex[i].x,mVertex[i].y,mVertex[i].z);
									stripcount+=1;
								}

							}
							//g - model name
							fprintf(objFile,"\ng model%d\n",model_number);
							//f - faces
							if (vertex_Count > 0)
							{
								for (int i = 0; i < stripcount;i+=3)
								{
									fprintf(objFile,"f %d %d %d\n",vertex_Count + i,vertex_Count + i+1,vertex_Count + i+2);
								}
								vertex_Count += stripcount;
							}else
							{
								for (int i = 1; i < stripcount+1;i+=3)
								{
									fprintf(objFile,"f %d %d %d\n",vertex_Count + i,vertex_Count + i+1,vertex_Count + i+2);
								}
								vertex_Count += stripcount+1;
							}
						}else
							if(vertexType == 5)
							{
								model_number++;
								fprintf(objFile,"\n");

								int fancount = 0;
								for(int i = 1; i < vertexCount - 1;i++)
								{
									fprintf(objFile,"v %f %f %f\n",mVertex[0].x,mVertex[0].y,mVertex[0].z);
									fprintf(objFile,"v %f %f %f\n",mVertex[i].x,mVertex[i].y,mVertex[i].z);
									fprintf(objFile,"v %f %f %f\n",mVertex[i+1].x,mVertex[i+1].y,mVertex[i+1].z);
									fancount+=3;
								}
								//g - model name
								fprintf(objFile,"\ng model%d\n",model_number);
								//f - faces
								if (vertex_Count > 0)
								{
									for (int i = 0; i < fancount;i+=3)
									{
										fprintf(objFile,"f %d %d %d\n",vertex_Count + i,vertex_Count + i+1,vertex_Count + i+2);
									}
									vertex_Count += fancount;
								}else
								{
									for (int i = 1; i < fancount+1;i+=3)
									{
										fprintf(objFile,"f %d %d %d\n",vertex_Count + i,vertex_Count + i+1,vertex_Count + i+2);
									}
									vertex_Count += fancount+1;
								}
							}
				}
				
			}

			fclose(binaryFile);		
				
		}
		
	}
	FindClose(hFind);

	fclose(objFile);

	system("pause");

	return 0;
}

