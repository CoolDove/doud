using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace doudcs
{
    class DoudCore
    {
        [DllImport("dcore", EntryPoint = "DWTKCreateWindow")]
        private static extern void CreateWindow(IntPtr instance, string cmd_line, int show_code);

        public static void CreateWindow(string cmd_line) {
            CreateWindow(Process.GetCurrentProcess().Handle, cmd_line, 1);
        }
        [DllImport("dcore", EntryPoint = "DWTKProcessWindowEvent")]
        public static extern int ProcessEvent();
    }
}
