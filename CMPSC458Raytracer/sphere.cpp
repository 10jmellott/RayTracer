#include "sphere.h"

//constructor given  center, radius, and material
sphere::sphere(Vec3f c, float r, int m, scene* s) : rtObject(s)  
{
	center = c;
	radius = r;
	matIndex = m;
	myScene = s;
}

float sphere::testIntersection(Vec3f eye, Vec3f dir)
{
	float disc = pow(dir.Dot3(eye - center), 2) - dir.Dot3(dir) * ((eye - center).Dot3(eye - center) - radius * radius);
	if(disc < 0) return MAX_DIST;
	float t1 = (-1 * dir.Dot3(eye - center) + sqrt(disc)) / dir.Dot3(dir);
	float t2 = (-1 * dir.Dot3(eye - center) - sqrt(disc)) / dir.Dot3(dir);
	return min(t1, t2);
}

Vec3f sphere::getNormal(Vec3f eye, Vec3f dir)
{
	//once you can test for intersection,
	//simply add (distance * view direction) to the eye location to get surface location,
	//then subtract the center location of the sphere to get the normal out from the sphere
	Vec3f normal;

	//dont forget to normalize
	normal.Normalize();

	return normal;
}

Vec3f sphere::getTextureCoords(Vec3f eye, Vec3f dir)
{
	//find the normal as in getNormal

	//use these to find spherical coordinates
	Vec3f x(1,0,0);
	Vec3f z(0,0,1);

	//phi is the angle down from z
	//theta is the angle from x curving toward y
	//hint: angle between two vectors is the acos() of the dot product

	//find phi using normal and z

	//find the x-y projection of the normal

	//find theta using the x-y projection and x

	//if x-y projection is in quadrant 3 or 4, then theta=2*PI-theta
	
	//return coordinates scaled to be between 0 and 1
	Vec3f coords;
	return coords;
}