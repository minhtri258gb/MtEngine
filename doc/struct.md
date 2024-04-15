# main.cpp - main()
	- Game.cpp - run()

# graphic
	* render
		- có shader: ShaderProgramMgr (khởi tạo và thêm sự kiện cho shader)
		- có VAO: Tạo model và thêm vào scene hoặc gui

# Input
* Init call back:
	- Graphic.init
		- cbk_cursor_pos -> Input::ins.cursorPos
		- cbk_key -> Input::ins.keyPress
		- cbk_mouse_button -> Input::ins.keyPress
* Command
	- Game.framework -> this->cmd.update
