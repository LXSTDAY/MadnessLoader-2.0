#pragma once

/* CRect class describes a rectangle.

	A(left;top)_____________________
	|                               |
	|                               |
	|                               |
	|_________________B(right;bottom)
	
*/
#pragma pack(push, 1)
class CRect
{
public:
	float left;          // x1
	float bottom;        // y1
	float right;         // x2
	float top; 
};
#pragma pack(pop)