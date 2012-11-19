#include "triangle.h"

float x3Det(Vec3f *c1, Vec3f *c2, Vec3f *c3)
{
	float prod1 = c1->x() * (c2->y() * c3->z() - c2->z() * c3->y());
	float prod2 = c2->x() * (c3->y() * c1->z() - c3->z() * c1->y());
	float prod3 = c3->x() * (c1->y() * c2->z() - c1->z() * c2->y());

	return prod1 + prod2 + prod3;
}

//constructor given  center, radius, and material
triangle::triangle(Vec3f p0, Vec3f p1, Vec3f p2, float tx0, float tx1, float tx2, float ty0, float ty1, float ty2, int m, scene* s) : rtObject(s)  
{
	point0 = p0;
	point1 = p1;
	point2 = p2;
	texX0 = tx0;
	texX1 = tx1;
	texX2 = tx2;
	texY0 = ty0;
	texY1 = ty1;
	texY2 = ty2;
	matIndex = m;
	myScene = s;
}

float triangle::testIntersection(Vec3f eye, Vec3f dir)
{
	Vec3f b =    point0 - eye;
	Vec3f amb =  point0 - point1;
	Vec3f amc =  point0 - point2;

	float detA = x3Det(&amb, &amc, &dir);
	if(detA == 0)
		return MAX_DIST;

	float t = x3Det(&amb, &amc, &b) / detA;
	float B = x3Det(&b, &amc, &dir) / detA;
	float G = x3Det(&amb, &b, &dir) / detA;

	if(t < 0)
		return MAX_DIST;
	if(B < 0 || B > 1)
		return MAX_DIST;
	if(G < 0 || G > 1 - B)
		return MAX_DIST;

	return t;
}

Vec3f triangle::getNormal(Vec3f eye, Vec3f dir)
{
	//construct the barycentric coordinates for the plane
	Vec3f bary1 = point1-point0;
	Vec3f bary2 = point2-point0;

	//cross them to get the normal to the plane
	//note that the normal points in the direction given by right-hand rule
	//(this can be important for refraction to know whether you are entering or leaving a material)
	Vec3f normal;
	Vec3f::Cross3(normal,bary1,bary2);
	normal.Normalize();

	return normal;
}

Vec3f triangle::getTextureCoords(Vec3f eye, Vec3f dir)
{
	//find alpha and beta (parametric distance along barycentric coordinates)
	//use these in combination with the known texture surface location of the vertices
	//to find the texture surface location of the point you are seeing

	Vec3f coords;

	Vec3f b =    point0 - eye;
	Vec3f amb =  point0 - point1;
	Vec3f amc =  point0 - point2;

	float detA = x3Det(&amb, &amc, &dir);
	float B = x3Det(&b, &amc, &dir) / detA;
	float G = x3Det(&amb, &b, &dir) / detA;

	Vec3f tex_amb = Vec3f(texX1 - texX0, texY1 - texY0, 0);
	//tex_amb.Normalize();
	Vec3f tex_amc = Vec3f(texX2 - texX0, texY2 - texY0, 0);
	//tex_amc.Normalize();

	coords = Vec3f(texX0, texY0, 0) + tex_amb * B + tex_amc * G;

	return coords;
}