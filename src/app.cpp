#include "engine/fr.hpp"
#include "engine/renderer/window.hpp"

using namespace fr;
using namespace renderer;

int main(int argc, char** argv) {
	frwindow* wnd = frwindow::Create();
	frWindowsManager::Initialize();
	wnd->Initialize("test", { 800, 600 });
	while (wnd->IsRunning()) {

		frWindowsManager::PollEvents();
	}
	return 0;
}
