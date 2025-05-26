


class CometaMath {

public: 
	inline static int BoundMax(int value, int max) {
		if (value > max) {
			return max; 
		}
		return value; 
	}

	inline static float BoundMax(float value, float max) {
		if (value > max) {
			return max; 
		}
		return value; 
	}

	inline static float Scope(float value, float min, float max) {
		if (value > max) {
			return max; 
		}
		else if (value < min) {
			return min; 
		}

		return value; 
	}


};