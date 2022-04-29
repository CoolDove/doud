using System;

namespace doudcs
{
    class Program
    {
        static void Main(string[] args)
        {
            DoudCore.CreateWindow("");

            int result = 1;
            while (result != 0) {
                DoudCore.ProcessEvent();
            }
            
        }
    }
}
