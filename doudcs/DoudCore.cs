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
        [DllImport("dcore")]
        private static extern void DWTKCreateWindow(IntPtr instance, string cmd_line, int show_code);
        public static void DWTKCreateWindow(string cmd_line) {
            DWTKCreateWindow(Process.GetCurrentProcess().Handle, cmd_line, 1);
        }

        [DllImport("dcore")]
        public static extern void DWTKRun();
    }
}
