#include <iostream>

#include <newton/dgNewton/Newton.h>
#include <newton/dMath/dVector.h>
#include <newton/dMath/dMatrix.h>


// Callback cho việc tính toán lực hấp dẫn (nếu cần tùy chỉnh)
void PhysicsApplyForceAndTorque(const NewtonBody* body, dFloat timestep, int threadIndex) {
	dFloat mass;
	dFloat Ixx, Iyy, Izz;

	// Lấy khối lượng và mô men quán tính
	NewtonBodyGetMass(body, &mass, &Ixx, &Iyy, &Izz);

	// Áp dụng trọng lực
	dVector gravity(0.0f, -9.8f * mass, 0.0f);
	NewtonBodySetForce(body, &gravity.m_x);
}

int main() {
	// Tạo thế giới Newton
	NewtonWorld* world = NewtonCreate();

	// Thiết lập các tham số cơ bản
	// NewtonSetSolverModel(world, 0);

	// Tạo một thân vật lý đơn giản (ví dụ: khối hộp)
	dVector boxSize(1.0f, 1.0f, 1.0f);
	dMatrix matrix(dGetIdentityMatrix());
	NewtonCollision* collision = NewtonCreateBox(world, boxSize.m_x, boxSize.m_y, boxSize.m_z, 0, NULL);
	NewtonBody* body = NewtonCreateDynamicBody(world, collision, &matrix[0][0]);

	// Gán khối lượng và callback lực
	NewtonBodySetMassProperties(body, 1.0f, collision);
	NewtonBodySetForceAndTorqueCallback(body, PhysicsApplyForceAndTorque);

	// Giải phóng bộ nhớ của đối tượng collision
	NewtonDestroyCollision(collision);

	// Vòng lặp mô phỏng vật lý
	const dFloat timestep = 1.0f / 60.0f;
	for (int i = 0; i < 600; i++) {  // Chạy 10 giây mô phỏng
		NewtonUpdate(world, timestep);
		std::cout << "Step: " << i << std::endl;
	}

	// Dọn dẹp
	NewtonDestroy(world);

	return 0;
}
