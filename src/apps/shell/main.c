//  _____          _____  ______
// / ____|   /\   |  __ \|  ____|
// | |       /  \  | |  | | |__
// | |      / /\ \ | |  | |  __|
// | |____ / ____ \| |__| | |____
// \_____/_/    \_\_____/|______|

/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   13-09-2016 19:09:68
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 22-09-2016 15:09:24
* @License: MIT
*/
#include <stdio.h>
#include "classes/cade-shell-application.h"

int main(int argc, char **argv)
{
  CadeShellApplication *shell = cade_shell_application_new();
  g_application_run(G_APPLICATION(shell), argc, argv);
  return 0;
}
