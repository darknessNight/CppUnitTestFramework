using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace darknessNight.CppUnitTest.VSAdapter.UnitTests {
    static class IntegrationsPaths {
        public static string[] getExampleTestsAssemblyPath() {
            //NOTE: path to solution Debug/Release dir from unit test assembly path
            var dllPath1 = AppDomain.CurrentDomain.BaseDirectory + "../../../Debug/CppUnitTestFrameworkExamples.dll";
            var dllPath2 = AppDomain.CurrentDomain.BaseDirectory + "../../../Release/CppUnitTestFrameworkExamples.dll";
            return new string[] { dllPath1, dllPath2 };
        }

        public static string getExampleTestPath() {
#if DEBUG
            return AppDomain.CurrentDomain.BaseDirectory + "../../../Debug/CppUnitTestFrameworkExamples.dll";
#else
            return AppDomain.CurrentDomain.BaseDirectory + "../../../Release/CppUnitTestFrameworkExamples.dll";
#endif
        }
    }
}
