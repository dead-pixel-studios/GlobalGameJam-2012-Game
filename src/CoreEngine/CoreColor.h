#pragma once

class CoreColor {
public:
	int r;
	int g;
	int b;
	int a;

	Uint32 rgba(){
		Uint8 arr[4];
		arr[3]=r;
		arr[2]=g;
		arr[1]=b;
		arr[0]=a;

		return *reinterpret_cast<Uint32*>(arr);
	}
};