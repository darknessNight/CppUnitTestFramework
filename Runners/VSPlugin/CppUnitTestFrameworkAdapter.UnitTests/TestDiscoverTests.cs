using NUnit.Framework;
using NSubstitute;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Logging;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Adapter;
using Microsoft.VisualStudio.TestPlatform.ObjectModel;

namespace darknessNight.CppUnitTest.VSAdapter.UnitTests {
    [TestFixture]
    public class TestDiscoverTests {
        [Test]
        public void TestReadAllSources_HasBasicArray_CheckSendsNamesToLogger() {
            List<string> usedPath = new List<string>();
            IMessageLogger fakeLogger = prepareFakeLoggerForGetMessages(usedPath);
            actTestReadSampleSources(fakeLogger);
            assertTestReadAllSources(usedPath);
        }

        private static void actTestReadSampleSources(IMessageLogger fakeLogger) {
            var container = Substitute.For<ITestCaseDiscoverySink>();
            TestDiscover discover = new TestDiscover();
            discover.DiscoverTests(new string[] { "../1.dll", "../2.dll" }, null, fakeLogger, container);
        }

        private static void assertTestReadAllSources(List<string> usedPath) {
            var listOfCorrectMessages = new string[] { "Tests found: 0", "Has: ../1.dll", "Has: ../2.dll", "----CppUnitTestAdapter:Ended----", "----CppUnitTestAdapter:Started----" };
            CollectionAssert.AreEquivalent(listOfCorrectMessages, usedPath);
        }

        private static IMessageLogger prepareFakeLoggerForGetMessages(List<string> messages) {
            var fakeLogger = Substitute.For<IMessageLogger>();
            fakeLogger.SendMessage(Arg.Any<TestMessageLevel>(), Arg.Do<string>(messages.Add));
            return fakeLogger;
        }

        [Test]
        public void TestTryReadLibrary_HasNonExistsLibraryPath_CheckNoThrow() {
            List<string> messages = new List<string>();
            TestDiscover discover = new TestDiscover();
            var fakeLogger = prepareFakeLoggerForGetMessages(messages);
            var container = Substitute.For<ITestCaseDiscoverySink>();
            TestDelegate test = () => { discover.DiscoverTests(new string[] { "Unexists.dll" }, null, fakeLogger, container); };
            Assert.DoesNotThrow(test);
        }

        [Test]
        public void TestTryReadLibrary_HasCorrectLibrary_CheckSendTestCase() {
            List<TestCase> loadedCases = new List<TestCase>();
            ITestCaseDiscoverySink container = PrepareFakeContainerForGetLoadedCases(loadedCases);
            ActDiscoverExistingTests(container);
            AssertSendCorrectCases(loadedCases);
        }

        private static void ActDiscoverExistingTests(ITestCaseDiscoverySink container) {
            string[] dllPaths = IntegrationsPaths.getExampleTestsAssemblyPath();
            var fakeLogger = Substitute.For<IMessageLogger>();
            TestDiscover discover = new TestDiscover();
            discover.DiscoverTests(dllPaths, null, fakeLogger, container);
        }

        private static void AssertSendCorrectCases(List<TestCase> loadedCases) {
            AssertSendCorrrectCountOFcases(loadedCases);
            AssertSendCorrectCase(loadedCases);
        }

        private static void AssertSendCorrectCase(List<TestCase> loadedCases) {
            bool found = checkHasCaseWithName(loadedCases, "IgnoredMethod");
            Assert.IsTrue(found, "Not founded test");
        }

        private static bool checkHasCaseWithName(List<TestCase> loadedCases, string caseName) {
            bool found = false;
            foreach (var test in loadedCases)
                if (test.FullyQualifiedName.Contains(caseName))
                    found = true;
            return found;
        }

        private static void AssertSendCorrrectCountOFcases(List<TestCase> loadedCases) {
            Assert.GreaterOrEqual(loadedCases.Count, 1);
        }

        private static ITestCaseDiscoverySink PrepareFakeContainerForGetLoadedCases(List<TestCase> loadedCases) {
            var container = Substitute.For<ITestCaseDiscoverySink>();
            container.SendTestCase(Arg.Do<TestCase>(loadedCases.Add));
            return container;
        }
    }
}
