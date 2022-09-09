#pragma once

#include "utils/error_handler.h"

#include <algorithm>
#include <linalg.h>
#include <vector>


using namespace linalg::aliases;

namespace cg
{
	template<typename T>
	class resource
	{
	public:
		resource(size_t size);
		resource(size_t x_size, size_t y_size);
		~resource();

		const T* get_data();
		T& item(size_t item);
		T& item(size_t x, size_t y);

		size_t get_size_in_bytes() const;
		size_t get_number_of_elements() const;
		size_t get_stride() const;

	private:
		std::vector<T> data;
		size_t item_size = sizeof(T);
		size_t stride;
	};

	template<typename T>
	inline resource<T>::resource(size_t size)
	{
		data.resize(size);
		stride = 0;
		// TODO Lab: 1.02 Implement `cg::resource` class
	}
	template<typename T>
	inline resource<T>::resource(size_t x_size, size_t y_size)
	{
		data.resize(x_size * y_size);
		stride = x_size;
		// TODO Lab: 1.02 Implement `cg::resource` class
	}
	template<typename T>
	inline resource<T>::~resource()
	{
	}
	template<typename T>
	inline const T* resource<T>::get_data()
	{
		// TODO Lab: 1.02 Implement `cg::resource` class
		return data.data();
	}
	template<typename T>
	inline T& resource<T>::item(size_t item)
	{
		// TODO Lab: 1.02 Implement `cg::resource` class
		return data.at(item);
	}
	template<typename T>
	inline T& resource<T>::item(size_t x, size_t y)
	{
		// TODO Lab: 1.02 Implement `cg::resource` class
		return data.at(y * stride + x);
	}
	template<typename T>
	inline size_t resource<T>::get_size_in_bytes() const
	{
		// TODO Lab: 1.02 Implement `cg::resource` class
		return data.size() * item_size;
	}
	template<typename T>
	inline size_t resource<T>::get_number_of_elements() const
	{
		// TODO Lab: 1.02 Implement `cg::resource` class
		return data.size();
	}

	template<typename T>
	inline size_t resource<T>::get_stride() const
	{
		// TODO Lab: 1.02 Implement `cg::resource` class
		return stride;
	}

	struct color
	{
		static color from_float3(const float3& in)
		{
			// TODO Lab: 1.02 Implement `cg::color` and `cg::unsigned_color` structs
			return color{in.x, in.y, in.z};
		};
		float3 to_float3() const
		{
			// TODO Lab: 1.02 Implement `cg::color` and `cg::unsigned_color` structs
			return float3{r, g, b};
		}
		float r;
		float g;
		float b;
	};

	struct unsigned_color
	{
		static unsigned_color from_color(const color& color)
		{
			// TODO Lab: 1.02 Implement `cg::color` and `cg::unsigned_color` structs
			unsigned_color out{};
			out.r = std::clamp(static_cast<int>(255.f * color.r), 0, 255);
			out.g = std::clamp(static_cast<int>(255.f * color.g), 0, 255);
			out.b = std::clamp(static_cast<int>(255.f * color.b), 0, 255);
			return out;
		};
		static unsigned_color from_float3(const float3& color)
		{
			// TODO Lab: 1.02 Implement `cg::color` and `cg::unsigned_color` structs
			unsigned_color out{};
			float3 preprocessed = clamp(255.f * color, 0.f, 255.f);
			out.r = static_cast<uint8_t> (preprocessed.x);
			out.g = static_cast<uint8_t> (preprocessed.y);
			out.b = static_cast<uint8_t> (preprocessed.z);
			return out
		};
		float3 to_float3() const
		{
			// TODO Lab: 1.02 Implement `cg::color` and `cg::unsigned_color` structs
			return float3{static_cast<float>(r),
						  static_cast<float>(g),
						  static_cast<float>(b)} /
				   255.f;
		};
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};


	struct vertex
	{
		// TODO Lab: 1.03 Implement `cg::vertex` struct
	};

}// namespace cg