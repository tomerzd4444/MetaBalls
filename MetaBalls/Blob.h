#pragma once


namespace MetaBalls {
	class Blob {
	public:
		Blob();
		Blob(float[]);
		Blob(float, float);
		float* pos;
		float* vel;
		float r;
		void show();
		void update();
	};
}