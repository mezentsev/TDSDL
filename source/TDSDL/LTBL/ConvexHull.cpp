#include "LTBL/ConvexHull.h"

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace ltbl;
using namespace qdt;

ConvexHull::ConvexHull()
	: worldCenter(0.0f, 0.0f),
	shadowDepthOffset(0.0f),
	aabbGenerated(false),
	updateRequired(true) // Remains true permanently unless user purposely changes it
{
}

void ConvexHull::CenterHull()
{
	// Calculate the average of all of the vertices, and then
	// offset all of them to make this the new origin position (0,0)
	const unsigned int numVertices = vertices.size();

	Vec2f posSum(0.0f, 0.0f);
	
	for(unsigned int i = 0; i < numVertices; i++)
		posSum += vertices[i].position;

	Vec2f averagePos = posSum / static_cast<float>(numVertices);

	for(unsigned int i = 0; i < numVertices; i++)
		vertices[i].position -= averagePos;
}

bool ConvexHull::LoadShape(const char* fileName)
{
	std::ifstream load(fileName);

	if(!load)
	{
		load.close();
		std::cout << "Load failed!" << std::endl;
		
		return false;
	}
	else
	{
		while(true) // While not at end of file
		{
			std::string firstElement, secondElement;

			load >> firstElement >> secondElement;

			if(firstElement.size() == 0 || secondElement.size() == 0)
			{
				load.close();
				break;
			}

			ConvexHullVertex newVertex;
			newVertex.position.x = static_cast<float>(GetFloatVal(firstElement));
			newVertex.position.y = static_cast<float>(GetFloatVal(secondElement));

			vertices.push_back(newVertex);
		}
	}

	CenterHull();

	CalculateNormals();

	return true;
}

Vec2f ConvexHull::GetWorldVertex(unsigned int index) const
{
	assert(index >= 0 && index < vertices.size());
	return Vec2f(vertices[index].position.x + worldCenter.x, vertices[index].position.y + worldCenter.y);
}

void ConvexHull::CalculateNormals()
{
	const unsigned int numVertices = vertices.size();

	if(normals.size() != numVertices)
		normals.resize(numVertices);

	for(unsigned int i = 0; i < numVertices; i++) // Dots are wrong
	{
		unsigned int index2 = i + 1;

		// Wrap
		if(index2 >= numVertices)
			index2 = 0;

		normals[i].x = -(vertices[index2].position.y - vertices[i].position.y);
		normals[i].y = vertices[index2].position.x - vertices[i].position.x;
	}
}

void ConvexHull::RenderHull(float depth)
{
	glBegin(GL_TRIANGLE_FAN);

	const unsigned int numVertices = vertices.size();
	
	for(unsigned int i = 0; i < numVertices; i++)
	{
		Vec2f vPos(GetWorldVertex(i));
		glVertex3f(vPos.x, vPos.y, depth);
	}

	glEnd();
}

void ConvexHull::GenerateAABB()
{
	assert(vertices.size() > 0);

	aabb.lowerBound = vertices[0].position;
	aabb.upperBound = aabb.lowerBound;

	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		Vec2f* pPos = &vertices[i].position;

		if(pPos->x > aabb.upperBound.x)
			aabb.upperBound.x = pPos->x;

		if(pPos->y > aabb.upperBound.y)
			aabb.upperBound.y = pPos->y;

		if(pPos->x < aabb.lowerBound.x)
			aabb.lowerBound.x = pPos->x;

		if(pPos->y < aabb.lowerBound.y)
			aabb.lowerBound.y = pPos->y;
	}

	aabbGenerated = true;
}

bool ConvexHull::HasGeneratedAABB()
{
	return aabbGenerated;
}

void ConvexHull::SetWorldCenter(const Vec2f &newCenter)
{
	worldCenter = newCenter;

	aabb.SetCenter(worldCenter);

	UpdateTreeStatus();
}

void ConvexHull::IncWorldCenter(const Vec2f &increment)
{
	worldCenter += increment;

	aabb.IncCenter(increment);

	UpdateTreeStatus();
}

Vec2f ConvexHull::GetWorldCenter() const
{
	return worldCenter;
}

bool ConvexHull::PointInsideHull(const Vec2f &point)
{
	const unsigned int numVertices = vertices.size();
	int sgn = 0;

	for(unsigned int i = 0; i < numVertices; i++)
	{
		int wrappedIndex = Wrap(i + 1, numVertices);
		Vec2f currentVertex(GetWorldVertex(i));
		Vec2f side(GetWorldVertex(wrappedIndex) - currentVertex);
		Vec2f toPoint(point - currentVertex);

		float cpd = side.cross(toPoint);

		int cpdi = static_cast<int>(cpd / abs(cpd));

		if(sgn == 0)
			sgn = cpdi;
		else if(cpdi != sgn)
			return false;
	}

	return true;
}

float ltbl::GetFloatVal(std::string strConvert)
{
	return static_cast<float>(atof(strConvert.c_str()));
}
