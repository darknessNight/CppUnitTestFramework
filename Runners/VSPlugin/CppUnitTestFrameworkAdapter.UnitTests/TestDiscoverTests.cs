using NUnit.Framework;
using NSubstitute;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Logging;

namespace darknessNight.CppUnitTest.VSAdapter.UnitTests {
    [TestFixture]
    public class TestDiscoverTests {
        [Test]
        public void TestReadAllSources_HasBasicArray_CheckSendsNamesToLogger() {
            List<string> usedPath = new List<string>();
            IMessageLogger fakeLogger = prepareFakeLoggerForGetListUsedpath(usedPath);
            actTestReadSampleSources(fakeLogger);
            assertTestReadAllSources(usedPath);
        }

        private static void actTestReadSampleSources(IMessageLogger fakeLogger) {
            TestDiscover discover = new TestDiscover();
            discover.DiscoverTests(new string[] { "../1.dll", "../2.dll" }, null, fakeLogger, null);
        }

        private static void assertTestReadAllSources(List<string> usedPath) {
            var listOfCorrectMessages = new string[] { "Has: ../1.dll", "Has: ../2.dll", "----CppUnitTestAdapter:Ended----", "----CppUnitTestAdapter:Started----" };
            CollectionAssert.AreEquivalent(listOfCorrectMessages, usedPath);
        }

        private static IMessageLogger prepareFakeLoggerForGetListUsedpath(List<string> usedPath) {
            var fakeLogger = Substitute.For<IMessageLogger>();
            fakeLogger.SendMessage(Arg.Any<TestMessageLevel>(), Arg.Do<string>((arg) => {
                usedPath.Add(arg);
            }));
            return fakeLogger;
        }
    }
}
