
# Commit

# BUG
- [X] kiểm tra FPS
- [ ] Text - VAO ko update dynamic được

# UI
- [ ] Nhập thư viện ImGUI
- [ ] Mở 1 cửa sổ khi nhấn F1
- [ ] Mở console khi nhấn `
- [ ] ...

# Player
- [X] gắn vào người chơi
- [X] đi lòng vòng
- [ ] tạo heightmap field
- [ ] đi trên đó

# Graphic
- [ ] Tạo DebugFrame để test render
- [ ] Sprite
	- [ ] Len Flare
- [ ] HUD
	- [ ] Text
		- [ ] FPS


# Physic body plane
- [Chưa test] Đã sửa lỗi phương trình mặt phẳng planeConst thay vì tham số scale
- [ ] Lỗi chưa set vị trí ban đầu cho ControlBody được -> Player chưa có vị trí ban đầu theo config

# StackTrace
* backward-cpp-1.6
	- ref: https://github.com/bombela/backward-cpp
* cpptrace-0.5.2
	- ref: https://github.com/jeremy-rifkin/cpptrace

# Quaternion
* Combile
	- [ ] test thử lại thử đổi chiều phép quay xem
		- res/maps/test.cfg
		- res/models/animals/fox/info.cfg

# Frustum culling
- [ ] Frustum culling Loi
	- vec3(128,0,128) dang la vec3(0,0,0) ?????????????????????????

# Terrain
- [ ] Đang làm thêm cho Static Terrain vướng vấn đề trên
	> Thêm scale width, length
	> thêm position cho terrain
	> Thêm texture cho static terrain
- [ ] Lỗi texture static terrain
