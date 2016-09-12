using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace darknessNight.CppUnitTest.VSAdapter.UnitTests {
    class IntegrationsPaths {
        public static string[] getExampleTestsAssemblyPath() {
            //NOTE: path to solution Debug/Release dir from unit test assembly path
            var dllPath1 = AppDomain.CurrentDomain.BaseDirectory + "../../../Debug/CppUnitTestFrameworkExamples.dll";
            var dllPath2 = AppDomain.CurrentDomain.BaseDirectory + "../../../Release/CppUnitTestFrameworkExamples.dll";
            return new string[] { dllPath1, dllPath2 };
        }
    }
}
