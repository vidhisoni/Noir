#pragma once

class Window
{
public:
	Window();
	~Window();
	void mOpenWindow();

private:
	void* pWindowHandle;
};