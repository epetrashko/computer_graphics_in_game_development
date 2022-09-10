#pragma once

#include "resource.h"

#include <cfloat>
#include <functional>
#include <iostream>
#include <linalg.h>
#include <memory>

using namespace linalg::aliases;

namespace cg::renderer
{
	template<typename VB, typename RT>
	class rasterizer
	{
	public:
		rasterizer(){};
		~rasterizer(){};
		void set_render_target(
				std::shared_ptr<resource<RT>> in_render_target,
				std::shared_ptr<resource<float>> in_depth_buffer = nullptr);
		void clear_render_target(
				const RT& in_clear_value, const float in_depth = FLT_MAX);

		void set_vertex_buffer(std::shared_ptr<resource<VB>> in_vertex_buffer);
		void set_index_buffer(std::shared_ptr<resource<unsigned int>> in_index_buffer);

		void set_viewport(size_t in_width, size_t in_height);

		void draw(size_t num_vertexes, size_t vertex_offest);

		std::function<std::pair<float4, VB>(float4 vertex, VB vertex_data)> vertex_shader;
		std::function<cg::color(const VB& vertex_data, const float z)> pixel_shader;

	protected:
		std::shared_ptr<cg::resource<VB>> vertex_buffer;
		std::shared_ptr<cg::resource<unsigned int>> index_buffer;
		std::shared_ptr<cg::resource<RT>> render_target;
		std::shared_ptr<cg::resource<float>> depth_buffer;

		size_t width = 1920;
		size_t height = 1080;

		float edge_function(float2 a, float2 b, float2 c);
		bool depth_test(float z, size_t x, size_t y);
	};

	template<typename VB, typename RT>
	inline void rasterizer<VB, RT>::set_render_target(
			std::shared_ptr<resource<RT>> in_render_target,
			std::shared_ptr<resource<float>> in_depth_buffer)
	{
		if (in_render_target)
			render_target = in_render_target;
		// TODO Lab: 1.02 Implement `set_render_target`, `set_viewport`, `clear_render_target` methods of `cg::renderer::rasterizer` class
		// TODO Lab: 1.06 Adjust `set_render_target`, and `clear_render_target` methods of `cg::renderer::rasterizer` class to consume a depth buffer
	}

	template<typename VB, typename RT>
	inline void rasterizer<VB, RT>::set_viewport(size_t in_width, size_t in_height)
	{
		height = in_height;
		width = in_width;
		// TODO Lab: 1.02 Implement `set_render_target`, `set_viewport`, `clear_render_target` methods of `cg::renderer::rasterizer` class
	}

	template<typename VB, typename RT>
	inline void rasterizer<VB, RT>::clear_render_target(
			const RT& in_clear_value, const float in_depth)
	{
		if (render_target) {
			for (size_t i = 0; i < render_target->get_number_of_elements(); i++) {
				render_target->item(i) = in_clear_value;
			}
		}
		// TODO Lab: 1.02 Implement `set_render_target`, `set_viewport`, `clear_render_target` methods of `cg::renderer::rasterizer` class
		// TODO Lab: 1.06 Adjust `set_render_target`, and `clear_render_target` methods of `cg::renderer::rasterizer` class to consume a depth buffer
	}

	template<typename VB, typename RT>
	inline void rasterizer<VB, RT>::set_vertex_buffer(
			std::shared_ptr<resource<VB>> in_vertex_buffer)
	{
		vertex_buffer = in_vertex_buffer;
	}

	template<typename VB, typename RT>
	inline void rasterizer<VB, RT>::set_index_buffer(
			std::shared_ptr<resource<unsigned int>> in_index_buffer)
	{
		index_buffer = in_index_buffer;
	}

	template<typename VB, typename RT>
	inline void rasterizer<VB, RT>::draw(size_t num_vertexes, size_t vertex_offset)
	{
		// TODO Lab: 1.04 Implement `cg::world::camera` class
		// TODO Lab: 1.05 Add `Rasterization` and `Pixel shader` stages to `draw` method of `cg::renderer::rasterizer`
		// TODO Lab: 1.06 Add `Depth test` stage to `draw` method of `cg::renderer::rasterizer`
		size_t vertex_id = vertex_offset;
		while (vertex_id < vertex_offset + num_vertexes) {
			std::vector<VB> vertices(3);
			vertices[0] = vertex_buffer->item(index_buffer->item(vertex_id++));
			vertices[1] = vertex_buffer->item(index_buffer->item(vertex_id++));
			vertices[2] = vertex_buffer->item(index_buffer->item(vertex_id++));

			for (auto& vertex: vertices) {
				float4 coord{
						vertex.x,
						vertex.y,
						vertex.z,
						1.f};
				auto processed_vertex = vertex_shader(coord, vertex);
				vertex.x = processed_vertex.first.x / processed_vertex.first.w;
				vertex.y = processed_vertex.first.y / processed_vertex.first.w;
				vertex.z = processed_vertex.first.z / processed_vertex.first.w;

				vertex.x = (vertex.x + 1.f) * width / 2.f;
				vertex.y = (vertex.y + 1.f) * height / 2.f;
			}
		}
	}

	template<typename VB, typename RT>
	inline float
	rasterizer<VB, RT>::edge_function(float2 a, float2 b, float2 c)
	{
		// TODO Lab: 1.05 Implement `cg::renderer::rasterizer::edge_function` method
		return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
	}

	template<typename VB, typename RT>
	inline bool rasterizer<VB, RT>::depth_test(float z, size_t x, size_t y)
	{
		// TODO Lab: 1.06 Implement `depth_test` function of `cg::renderer::rasterizer` class
		if (!depth_buffer)
		{
			return true;
		}
		return depth_buffer->item(x, y) > z;
	}

}// namespace cg::renderer