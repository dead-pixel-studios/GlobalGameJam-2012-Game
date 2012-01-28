#pragma once

class CoreColor {
public:
	int r;
	int g;
	int b;
	int a;

	Uint32 rgba(){
		Uint8 arr[4];
		arr[0]=r;
		arr[1]=g;
		arr[2]=b;
		arr[3]=a;

		return *reinterpret_cast<Uint32*>(arr);
	}
};