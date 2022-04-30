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
        [DllImport("dcore", EntryPoint = "InitApp")]
        public static extern void InitApp(IntPtr instance, string cmd_line);
        [DllImport("dcore", EntryPoint = "Run")]
        public static extern void Run();

        public static void InitApp(string cmd_line) {
            InitApp(Process.GetCurrentProcess().Handle, cmd_line);
        }
    }
}
