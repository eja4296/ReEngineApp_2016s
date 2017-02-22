#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}


void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

}

void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	// Half of the unit
	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1

	
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release(); // Release memory
	Init(); // initialize pointers to index 0

	//Your code starts here
	//3--2
	//|  |
	//0--1

	// std vector to hold all points
	std::vector<vector3> point;

	float theta = 0; // angle between each subdivision
	float steps = 2 * PI / a_nSubdivisions; // used to increment theta

	point.push_back(vector3(0.0, 0.0, 0.0)); // for origin
	
	// add points
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fRadius, 0, sin(theta)* a_fRadius));
		theta += steps;
	}

	// draw tri's
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[i], point[i+1], point[0]);
	}

	// draw last try
	AddTri(point[a_nSubdivisions], point[1], point[0]);
	
	point.push_back(vector3(0, a_fHeight, 0));

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[i], point[a_nSubdivisions + 1], point[i + 1]);
	}

	AddTri(point[a_nSubdivisions], point[a_nSubdivisions + 1], point[1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	// 2 std vectors 
	std::vector<vector3> point;
	std::vector<vector3> point2;

	float theta = 0; // angle between each subdivision
	float steps = 2 * PI / a_nSubdivisions;

	// Bottom "circle"
	vector3 bottomOrigin(0, 0, 0);
	point.push_back(bottomOrigin); // for origin

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fRadius, 0, sin(theta)* a_fRadius));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	// reset theta
	theta = 0;

	// Top "circle"
	vector3 topOrigin(0, a_fHeight, 0);
	point2.push_back(topOrigin);
	for (int i = 0; i < a_nSubdivisions; i++) {
		point2.push_back(vector3(cos(theta) * a_fRadius, a_fHeight, sin(theta)* a_fRadius));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point2[0], point2[i + 1], point2[i]);
	}

	// connect last 3 points
	AddTri(point2[0], point2[1], point2[a_nSubdivisions]);

	// Connect top and bottom
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddQuad(point2[i], point2[i+1], point[i], point[i + 1]);
	}

	// Connect last 4 points
	AddQuad(point2[a_nSubdivisions], point2[1], point[a_nSubdivisions], point[1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	// 2 std vectors 
	std::vector<vector3> pointsBottomOuter;
	std::vector<vector3> pointsTopOuter;
	std::vector<vector3> pointsBottomInner;
	std::vector<vector3> pointsTopInner;


	float theta = 0; // angle between each subdivision
	float steps = 2 * PI / a_nSubdivisions;

	// Bottom Outer "circle"
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsBottomOuter.push_back(vector3(cos(theta) * a_fOuterRadius, 0, sin(theta)* a_fOuterRadius));
		theta += steps;
	}

	// reset theta
	theta = 0;

	// Top Outer "circle"
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsTopOuter.push_back(vector3(cos(theta) * a_fOuterRadius, a_fHeight, sin(theta)* a_fOuterRadius));
		theta += steps;
	}

	// Connect bottom and top outer circles
	for (int i = 0; i < a_nSubdivisions-1; i++) {
		AddQuad(pointsTopOuter[i], pointsTopOuter[i + 1], pointsBottomOuter[i], pointsBottomOuter[i + 1]);
	}

	AddQuad(pointsTopOuter[a_nSubdivisions-1], pointsTopOuter[0], pointsBottomOuter[a_nSubdivisions - 1], pointsBottomOuter[0]);

	// reset theta
	theta = 0;

	// Bottom Inner "circle"
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsBottomInner.push_back(vector3(cos(theta) * a_fInnerRadius, 0, sin(theta)* a_fInnerRadius));
		theta += steps;
	}

	// reset theta
	theta = 0;

	// Top Inner "circle"
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsTopInner.push_back(vector3(cos(theta) * a_fInnerRadius, a_fHeight, sin(theta)* a_fInnerRadius));
		theta += steps;
	}

	// Connect top and bottom inner and outer circles
	for (int i = 0; i < a_nSubdivisions-1; i++) {
		AddQuad(pointsBottomInner[i], pointsBottomInner[i + 1], pointsTopInner[i], pointsTopInner[i + 1]);
	}

	AddQuad(pointsBottomInner[a_nSubdivisions - 1], pointsBottomInner[0], pointsTopInner[a_nSubdivisions - 1], pointsTopInner[0]);

	// Connect bottom inner and top outer circles
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(pointsBottomOuter[i], pointsBottomOuter[i + 1], pointsBottomInner[i], pointsBottomInner[i + 1]);
	}

	AddQuad(pointsBottomOuter[a_nSubdivisions - 1], pointsBottomOuter[0], pointsBottomInner[a_nSubdivisions - 1], pointsBottomInner[0]);

	// Connect top inner and top outer circles
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(pointsTopInner[i], pointsTopInner[i + 1], pointsTopOuter[i], pointsTopOuter[i + 1]);
	}

	AddQuad(pointsTopInner[a_nSubdivisions - 1], pointsTopInner[0], pointsTopOuter[a_nSubdivisions - 1], pointsTopOuter[0]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions >= 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	// std vector to hold all points

	//std::vector<vector3> point;
	std::vector<vector3> point;

	float theta = 0; // angle between each subdivision
	float thetaSteps = 2 * PI / a_nSubdivisions; // used to increment theta

	float phi = 0;
	float phiSteps = PI / a_nSubdivisions;

	// Formula for finding a 
	// point on the edge of a sphere
	// x = r * cos(theta) * sin(phi)
	// y = r * sin(theta) * sin(phi)
	// z = r * cos(phi)

	point.push_back(vector3(0.0, a_fRadius, 0.0));
	phi += phiSteps;
	
	// add all points to sphere
	for (int j = 0; j < a_nSubdivisions; j++)
	{
		for (int i = 0; i < a_nSubdivisions; i++) {
			point.push_back(vector3(cos(theta) * sin(phi) * a_fRadius, cos(phi) * a_fRadius, sin(theta)* sin(phi) * a_fRadius));
			theta += thetaSteps;
		}
		phi += phiSteps;
	}

	// Make top of sphere
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}
	
	AddTri(point[0], point[a_nSubdivisions], point[1]);
	
	// Make subdivisions of cirlce
	for (int j = 1; j < a_nSubdivisions-1; j++) {
		for (int i = 1; i < a_nSubdivisions; i++) {
			AddQuad(point[i + (a_nSubdivisions * j)], point[i + 1 + (a_nSubdivisions * j)], 
				point[i + ((j-1)*a_nSubdivisions)], point[i + 1 + ((j - 1)*a_nSubdivisions)]);
		}
		AddQuad(point[(j + 1) * a_nSubdivisions], point[1 + (j * a_nSubdivisions)], 
			point[j * a_nSubdivisions], point[1 + ((j-1) * a_nSubdivisions)]);
	}

	// Make bottom of circle
	point.push_back(vector3(0.0, -a_fRadius, 0.0));
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[(a_nSubdivisions * a_nSubdivisions) + 1], 
			point[i + 1 + (a_nSubdivisions * (a_nSubdivisions - 2))], 
			point[i + (a_nSubdivisions * (a_nSubdivisions - 2))]);
	}

	AddTri(point[a_nSubdivisions * (a_nSubdivisions - 1)], point[(a_nSubdivisions * a_nSubdivisions) + 1],
		point[1 + (a_nSubdivisions * (a_nSubdivisions - 2))]);
	
	//Your code ends here
	CompileObject(a_v3Color);
}