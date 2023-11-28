#pragma once
template <typename T>
inline float lerp(const T& a, const T& b, float t)
{
	return a + t * (b - a);
}