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
* @Last modified by:   marius
* @Last modified time: 12-10-2016 14:10:08
* @License: MIT
*/
#include <stdio.h>
#include <cade-core.h>

int main(int argc, char **argv)
{
  CadeShellApplication *shell = cade_shell_application_new();
  g_application_run(G_APPLICATION(shell), argc, argv);
  return 0;
}
