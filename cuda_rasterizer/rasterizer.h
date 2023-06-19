#ifndef CUDA_RASTERIZER_H_INCLUDED
#define CUDA_RASTERIZER_H_INCLUDED

#include <vector>

namespace CudaRasterizer
{
	struct InternalState;

	class Rasterizer
	{
	public:

		virtual InternalState* createInternalState() = 0;

		virtual void killInternalState(InternalState*) = 0;

		virtual void markVisible(
			int P,
			float* means3D,
			float* viewmatrix,
			float* projmatrix,
			bool* present) = 0;

		virtual void forward(
			const int P, int D, int M,
			const float* background,
			const int width, int height,
			const float* means3D,
			const float* shs,
			const float* colors_precomp,
			const float* opacities,
			const float* scales,
			const float scale_modifier,
			const float* rotations,
			const float* cov3D_precomp,
			const float* viewmatrix,
			const float* projmatrix,
			const float* cam_pos,
			const float tan_fovx, float tan_fovy,
			const bool prefiltered,
			int* radii,
			InternalState* state,
			float* out_color) = 0;

		virtual void backward(
			const int* radii,
			const InternalState* state,
			const int P, int D, int M,
			const float* background,
			const int width, int height,
			const float* means3D,
			const float* shs,
			const float* colors_precomp,
			const float* scales,
			const float scale_modifier,
			const float* rotations,
			const float* cov3D_precomp,
			const float* viewmatrix,
			const float* projmatrix,
			const float* campos,
			const float tan_fovx, float tan_fovy,
			const float* dL_dpix,
			float* dL_dmean2D,
			float* dL_dconic,
			float* dL_dopacity,
			float* dL_dcolor,
			float* dL_dmean3D,
			float* dL_dcov3D,
			float* dL_dsh,
			float* dL_dscale,
			float* dL_drot) = 0;

		virtual ~Rasterizer() {};

		static Rasterizer* make(int resizeMultipliyer = 2);

		static void kill(Rasterizer* rasterizer);
	};
};

#endif