#include <ode/ode.h>
#include <iostream>

// Hàm áp dụng lực hấp dẫn
void applyGravity(dBodyID body) {
	const dReal* pos = dBodyGetPosition(body);
	std::cout << "Body position: x = " << pos[0] << ", y = " << pos[1] << ", z = " << pos[2] << std::endl;

	// Áp dụng lực hấp dẫn
	dMass mass;
	dBodyGetMass(body, &mass);
	dBodyAddForce(body, 0, -9.8 * mass.mass, 0);
}

int main() {
	// Bước 1: Khởi tạo ODE
	dInitODE();

	// Bước 2: Tạo thế giới và không gian va chạm
	dWorldID world = dWorldCreate();
	dSpaceID space = dHashSpaceCreate(0);

	// Thiết lập các thông số thế giới
	dWorldSetGravity(world, 0, -9.8, 0);

	// Bước 3: Tạo vật thể động (Dynamic Body)
	dBodyID body = dBodyCreate(world);
	dMass mass;
	dMassSetSphere(&mass, 1, 1.0); // Hình cầu, khối lượng 1.0
	dBodySetMass(body, &mass);
	dBodySetPosition(body, 0, 10, 0); // Đặt vị trí ban đầu

	// Bước 4: Vòng lặp mô phỏng
	for (int i = 0; i < 100; ++i) {
		applyGravity(body);
		dWorldStep(world, 0.01); // Bước thời gian 0.01 giây
	}

	// Bước 5: Dọn dẹp
	dBodyDestroy(body);
	dSpaceDestroy(space);
	dWorldDestroy(world);
	dCloseODE();

	return 0;
}