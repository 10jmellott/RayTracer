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
	Vec3f normal;

	normal = (eye + dir * testIntersection(eye, dir)) - center;	
	normal.Normalize();

	return normal;
}

Vec3f sphere::getTextureCoords(Vec3f eye, Vec3f dir)
{
	Vec3f pt = (eye + dir * testIntersection(eye, dir)) - center;
	float theta = acos(pt.z() / radius);
	float phi = atan2(pt.y(), pt.x());

	float u = phi / 2 / PI;
	float v = 1 - (PI - theta) / PI;

	return Vec3f(u, v, 0);
}
