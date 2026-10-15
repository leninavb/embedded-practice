Makefile, makefile y MAKEFILE son archivos distintos, y lo mismo pasa con main.c y Main.c. Cuando algo “no se encuentra” y el nombre parece igual, revisa las mayúsculas.

lenin@andres:~/embedded-practice$ mkdir -p build
lenin@andres:~/embedded-practice$ gcc -Wall -Wextra -IUnity/src test/test_smoke.c Unity/src/unity.c -o build/test_smoke
./build/test_smoke
test/test_smoke.c: In function ‘main’:
test/test_smoke.c:13:5: error: expected declaration or statement at end of input
   13 |     return UNITY_END();
      |     ^~~~~~
bash: ./build/test_smoke: No such file or directory
lenin@andres:~/embedded-practice$ cat test/test_smoke.c
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_suma_basica(void) {
    TEST_ASSERT_EQUAL_INT(4, 2 + 2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_suma_basica);
    return UNITY_END();
lenin@andres:~/embedded-practice$ gcc -Wall -Wextra -IUnity/src test/test_smoke.c Unity/src/unity.c -o build/test_smokee
./build/test_smoke
test/test_smoke.c:12:test_suma_basica:PASS

-----------------------
1 Tests 0 Failures 0 Ignored 
OK
lenin@andres:~/embedded-practice$ make test
make: Nothing to be done for 'test'.
lenin@andres:~/embedded-practice$ make test
make: Nothing to be done for 'test'.
lenin@andres:~/embedded-practice$ ls -la
total 40
drwxr-xr-x 8 lenin lenin 4096 Oct 13 17:58 .
drwxr-x--- 8 lenin lenin 4096 Oct 13 17:49 ..
drwxr-xr-x 6 lenin lenin 4096 Oct 13 17:19 .git
-rw-r--r-- 1 lenin lenin    7 Oct 13 17:22 .gitignore
-rw-r--r-- 1 lenin lenin  254 Oct 13 18:00 MakeFile
-rw-r--r-- 1 lenin lenin    0 Oct 13 17:21 NOTAS.md
-rw-r--r-- 1 lenin lenin    0 Oct 13 17:21 README.md
drwxr-xr-x 9 lenin lenin 4096 Oct 13 17:21 Unity
drwxr-xr-x 2 lenin lenin 4096 Oct 13 17:57 build
drwxr-xr-x 2 lenin lenin 4096 Oct 13 17:19 include
drwxr-xr-x 2 lenin lenin 4096 Oct 13 17:19 src
drwxr-xr-x 2 lenin lenin 4096 Oct 13 17:52 test
lenin@andres:~/embedded-practice$ cat -A MakeFile
CC = gcc$
CFLAGS = -Wall -Wextra -Iinclude -IUnity/src$
UNITY = Unity/src/unity.c$
$
build/test_smoke: test/test_smoke.c $(UNITY)$
^I@mkdir -p build$
^I$(CC) $(CFLAGS) $^ -o $@$
$
test: build/test_smoke$
^I./build/test_smoke$
$
clean:$
^Irm -rf build$
$
.PHONY: test cleanlenin@andres:~/embedded-practice$ ls
Makefile  NOTAS.md  README.md  Unity  build  include  src  test
lenin@andres:~/embedded-practice$ make clean
rm -rf build
lenin@andres:~/embedded-practice$ make test
gcc -Wall -Wextra -Iinclude -IUnity/src test/test_smoke.c Unity/src/unity.c -o build/test_smoke
./build/test_smoke
test/test_smoke.c:12:test_suma_basica:PASS

-----------------------
1 Tests 0 Failures 0 Ignored 
OK
lenin@andres:~/embedded-practice$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        .gitignore
        Makefile
        NOTAS.md
        README.md
        Unity/
        test/

nothing added to commit but untracked files present (use "git add" to track)
lenin@andres:~/embedded-practice$ git add .
lenin@andres:~/embedded-practice$ git commit -m "Initial Setup with Unity and Smoke test"
[master (root-commit) 2d51790] Initial Setup with Unity and Smoke test
 179 files changed, 30762 insertions(+)
 create mode 100644 .gitignore
 create mode 100644 Makefile
 create mode 100644 NOTAS.md
 create mode 100644 README.md
 create mode 100644 Unity/.editorconfig
 create mode 100644 Unity/.gitattributes
 create mode 100644 Unity/.github/FUNDING.yml
 create mode 100644 Unity/.github/workflows/main.yml
 create mode 100644 Unity/.gitignore
 create mode 100644 Unity/CMakeLists.txt
 create mode 100644 Unity/LICENSE.txt
 create mode 100644 Unity/README.md
 create mode 100644 Unity/auto/__init__.py
 create mode 100644 Unity/auto/colour_prompt.rb
 create mode 100644 Unity/auto/colour_reporter.rb
 create mode 100755 Unity/auto/extract_version.py
 create mode 100644 Unity/auto/generate_config.yml
 create mode 100644 Unity/auto/generate_module.rb
 create mode 100755 Unity/auto/generate_test_runner.rb
 create mode 100644 Unity/auto/parse_output.rb
 create mode 100644 Unity/auto/stylize_as_junit.py
 create mode 100755 Unity/auto/stylize_as_junit.rb
 create mode 100644 Unity/auto/test_file_filter.rb
 create mode 100644 Unity/auto/type_sanitizer.rb
 create mode 100644 Unity/auto/unity_test_summary.py
 create mode 100755 Unity/auto/unity_test_summary.rb
 create mode 100644 Unity/auto/yaml_helper.rb
 create mode 100644 Unity/docs/CODE_OF_CONDUCT.md
 create mode 100644 Unity/docs/CONTRIBUTING.md
 create mode 100644 Unity/docs/MesonGeneratorRunner.md
 create mode 100644 Unity/docs/ThrowTheSwitchCodingStandard.md
 create mode 100644 Unity/docs/UnityAssertionsCheatSheetSuitableforPrintingandPossiblyFraming.pdf
 create mode 100644 Unity/docs/UnityAssertionsReference.md
 create mode 100644 Unity/docs/UnityChangeLog.md
 create mode 100644 Unity/docs/UnityConfigurationGuide.md
 create mode 100644 Unity/docs/UnityGettingStartedGuide.md
 create mode 100644 Unity/docs/UnityHelperScriptsGuide.md
 create mode 100644 Unity/docs/UnityKnownIssues.md
 create mode 100644 Unity/examples/example_1/makefile
 create mode 100644 Unity/examples/example_1/meson.build
 create mode 100644 Unity/examples/example_1/readme.txt
 create mode 100644 Unity/examples/example_1/src/ProductionCode.c
 create mode 100644 Unity/examples/example_1/src/ProductionCode.h
 create mode 100644 Unity/examples/example_1/src/ProductionCode2.c
 create mode 100644 Unity/examples/example_1/src/ProductionCode2.h
 create mode 100644 Unity/examples/example_1/subprojects/unity.wrap
 create mode 100644 Unity/examples/example_1/test/TestProductionCode.c
 create mode 100644 Unity/examples/example_1/test/TestProductionCode2.c
 create mode 100644 Unity/examples/example_1/test/test_runners/TestProductionCode2_Runner.c
 create mode 100644 Unity/examples/example_1/test/test_runners/TestProductionCode_Runner.c
 create mode 100644 Unity/examples/example_2/makefile
 create mode 100644 Unity/examples/example_2/readme.txt
 create mode 100644 Unity/examples/example_2/src/ProductionCode.c
 create mode 100644 Unity/examples/example_2/src/ProductionCode.h
 create mode 100644 Unity/examples/example_2/src/ProductionCode2.c
 create mode 100644 Unity/examples/example_2/src/ProductionCode2.h
 create mode 100644 Unity/examples/example_2/test/TestProductionCode.c
 create mode 100644 Unity/examples/example_2/test/TestProductionCode2.c
 create mode 100644 Unity/examples/example_2/test/test_runners/TestProductionCode2_Runner.c
 create mode 100644 Unity/examples/example_2/test/test_runners/TestProductionCode_Runner.c
 create mode 100644 Unity/examples/example_2/test/test_runners/all_tests.c
 create mode 100644 Unity/examples/example_3/helper/UnityHelper.c
 create mode 100644 Unity/examples/example_3/helper/UnityHelper.h
 create mode 100644 Unity/examples/example_3/project.yml
 create mode 100644 Unity/examples/example_3/rakefile.rb
 create mode 100644 Unity/examples/example_3/rakefile_helper.rb
 create mode 100644 Unity/examples/example_3/readme.txt
 create mode 100644 Unity/examples/example_3/src/ProductionCode.c
 create mode 100644 Unity/examples/example_3/src/ProductionCode.h
 create mode 100644 Unity/examples/example_3/src/ProductionCode2.c
 create mode 100644 Unity/examples/example_3/src/ProductionCode2.h
 create mode 100644 Unity/examples/example_3/test/TestProductionCode.c
 create mode 100644 Unity/examples/example_3/test/TestProductionCode2.c
 create mode 100644 Unity/examples/example_4/meson.build
 create mode 100644 Unity/examples/example_4/readme.txt
 create mode 100644 Unity/examples/example_4/src/ProductionCode.c
 create mode 100644 Unity/examples/example_4/src/ProductionCode.h
 create mode 100644 Unity/examples/example_4/src/ProductionCode2.c
 create mode 100644 Unity/examples/example_4/src/ProductionCode2.h
 create mode 100644 Unity/examples/example_4/src/meson.build
 create mode 100755 Unity/examples/example_4/subprojects/unity.wrap
 create mode 100644 Unity/examples/example_4/test/TestProductionCode.c
 create mode 100644 Unity/examples/example_4/test/TestProductionCode2.c
 create mode 100644 Unity/examples/example_4/test/meson.build
 create mode 100644 Unity/examples/example_4/test/test_runners/TestProductionCode2_Runner.c
 create mode 100644 Unity/examples/example_4/test/test_runners/TestProductionCode_Runner.c
 create mode 100644 Unity/examples/example_4/test/test_runners/meson.build
 create mode 100644 Unity/examples/example_5/makefile
 create mode 100644 Unity/examples/example_5/readme.txt
 create mode 100644 Unity/examples/example_5/src/ProductionCode.c
 create mode 100644 Unity/examples/example_5/src/ProductionCode.h
 create mode 100644 Unity/examples/example_5/subprojects/unity.wrap
 create mode 100644 Unity/examples/example_5/test/TestProductionCode.c
 create mode 100644 Unity/examples/example_5/test/test_runners/TestProductionCode_Runner.c
 create mode 100644 Unity/examples/example_5/test/unity_detail_config.h
 create mode 100644 Unity/examples/unity_config.h
 create mode 100644 Unity/extras/bdd/readme.md
 create mode 100644 Unity/extras/bdd/src/unity_bdd.h
 create mode 100644 Unity/extras/bdd/test/meson.build
 create mode 100644 Unity/extras/bdd/test/test_bdd.c
 create mode 100644 Unity/extras/eclipse/error_parsers.txt
 create mode 100644 Unity/extras/fixture/readme.md
 create mode 100644 Unity/extras/fixture/src/meson.build
 create mode 100644 Unity/extras/fixture/src/unity_fixture.c
 create mode 100644 Unity/extras/fixture/src/unity_fixture.h
 create mode 100644 Unity/extras/fixture/src/unity_fixture_internals.h
 create mode 100644 Unity/extras/fixture/test/main/AllTests.c
 create mode 100644 Unity/extras/fixture/test/template_fixture_tests.c
 create mode 100644 Unity/extras/fixture/test/unity_fixture_Test.c
 create mode 100644 Unity/extras/fixture/test/unity_fixture_TestRunner.c
 create mode 100644 Unity/extras/memory/readme.md
 create mode 100644 Unity/extras/memory/src/meson.build
 create mode 100644 Unity/extras/memory/src/unity_memory.c
 create mode 100644 Unity/extras/memory/src/unity_memory.h
 create mode 100644 Unity/extras/memory/test/unity_memory_Test.c
 create mode 100644 Unity/extras/memory/test/unity_memory_TestRunner.c
 create mode 100644 Unity/extras/memory/test/unity_output_Spy.c
 create mode 100644 Unity/extras/memory/test/unity_output_Spy.h
 create mode 100644 Unity/library.json
 create mode 100644 Unity/meson.build
 create mode 100644 Unity/meson_options.txt
 create mode 100644 Unity/platformio-build.py
 create mode 100644 Unity/src/meson.build
 create mode 100644 Unity/src/unity.c
 create mode 100644 Unity/src/unity.h
 create mode 100644 Unity/src/unity_internals.h
 create mode 100644 Unity/test/.rubocop.yml
 create mode 100644 Unity/test/expectdata/testsample_cmd.c
 create mode 100644 Unity/test/expectdata/testsample_def.c
 create mode 100644 Unity/test/expectdata/testsample_head1.c
 create mode 100644 Unity/test/expectdata/testsample_head1.h
 create mode 100644 Unity/test/expectdata/testsample_mock_cmd.c
 create mode 100644 Unity/test/expectdata/testsample_mock_def.c
 create mode 100644 Unity/test/expectdata/testsample_mock_head1.c
 create mode 100644 Unity/test/expectdata/testsample_mock_head1.h
 create mode 100644 Unity/test/expectdata/testsample_mock_new1.c
 create mode 100644 Unity/test/expectdata/testsample_mock_new2.c
 create mode 100644 Unity/test/expectdata/testsample_mock_param.c
 create mode 100644 Unity/test/expectdata/testsample_mock_run1.c
 create mode 100644 Unity/test/expectdata/testsample_mock_run2.c
 create mode 100644 Unity/test/expectdata/testsample_mock_yaml.c
 create mode 100644 Unity/test/expectdata/testsample_new1.c
 create mode 100644 Unity/test/expectdata/testsample_new2.c
 create mode 100644 Unity/test/expectdata/testsample_param.c
 create mode 100644 Unity/test/expectdata/testsample_run1.c
 create mode 100644 Unity/test/expectdata/testsample_run2.c
 create mode 100644 Unity/test/expectdata/testsample_yaml.c
 create mode 100644 Unity/test/rakefile
 create mode 100644 Unity/test/rakefile_helper.rb
 create mode 100644 Unity/test/spec/generate_module_existing_file_spec.rb
 create mode 100644 Unity/test/targets/clang.yml
 create mode 100644 Unity/test/targets/gcc.yml
 create mode 100644 Unity/test/targets/hitech_picc18.yml
 create mode 100644 Unity/test/targets/iar_arm.yml
 create mode 100644 Unity/test/targets/no_stdlib.yml
 create mode 100644 Unity/test/testdata/CException.h
 create mode 100644 Unity/test/testdata/Defs.h
 create mode 100644 Unity/test/testdata/cmock.h
 create mode 100644 Unity/test/testdata/mockMock.h
 create mode 100644 Unity/test/testdata/testRunnerGenerator.c
 create mode 100644 Unity/test/testdata/testRunnerGeneratorEmpty.c
 create mode 100644 Unity/test/testdata/testRunnerGeneratorSmall.c
 create mode 100644 Unity/test/testdata/testRunnerGeneratorWithMocks.c
 create mode 100644 Unity/test/tests/self_assessment_utils.h
 create mode 100644 Unity/test/tests/test_generate_test_runner.rb
 create mode 100644 Unity/test/tests/test_unity_arrays.c
 create mode 100644 Unity/test/tests/test_unity_core.c
 create mode 100644 Unity/test/tests/test_unity_doubles.c
 create mode 100644 Unity/test/tests/test_unity_floats.c
 create mode 100644 Unity/test/tests/test_unity_integers.c
 create mode 100644 Unity/test/tests/test_unity_integers_64.c
 create mode 100644 Unity/test/tests/test_unity_memory.c
 create mode 100644 Unity/test/tests/test_unity_parameterized.c
 create mode 100644 Unity/test/tests/test_unity_parameterizedDemo.c
 create mode 100644 Unity/test/tests/test_unity_strings.c
 create mode 100644 Unity/test/tests/test_unity_test_summary.rb
 create mode 100644 Unity/test/tests/types_for_test.h
 create mode 100644 Unity/unityConfig.cmake
 create mode 100644 test/test_smoke.c
lenin@andres:~/embedded-practice$ sudo apt install -y gh
[sudo: authenticate] Password:      
Installing:                     
  gh

Summary:
  Upgrading: 0, Installing: 1, Removing: 0, Not Upgrading: 101
  Download size: 8547 kB
  Space needed: 37.1 MB / 1023 GB available

Get:1 http://archive.ubuntu.com/ubuntu resolute/universe amd64 gh amd64 2.46.0-4 [8547 kB]
Fetched 8547 kB in 3s (2729 kB/s)
debconf: unable to initialize frontend: Dialog
debconf: (Dialog frontend requires a screen at least 13 lines tall and 31 columns wide.)
debconf: falling back to frontend: Readline
Selecting previously unselected package gh.
(Reading database ... 42681 files and directories currently installed.)
Preparing to unpack .../archives/gh_2.46.0-4_amd64.deb ...
Unpacking gh (2.46.0-4) ...
Setting up gh (2.46.0-4) ...
Processing triggers for man-db (2.13.1-1build1) ...
lenin@andres:~/embedded-practice$ gh auth login
? What account do you want to log into? GitHub.com
? What is your preferred protocol for Git operations on this host? HTTPS
? Authenticate Git with your GitHub credentials? Yes
? How would you like to authenticate GitHub CLI? Login with a web browser

! First copy your one-time code: D43A-2641
Press Enter to open github.com in your browser... 
! Failed opening a web browser at https://github.com/login/device
  exec: "xdg-open,x-www-browser,www-browser,wslview": executable file not found in $PATH
  Please try entering the URL in your browser manually
✓ Authentication complete.
- gh config set -h github.com git_protocol https
✓ Configured git protocol
! Authentication credentials saved in plain text
✓ Logged in as leninavb
lenin@andres:~/embedded-practice$ git remote add origin https://github.com/TU_USUARIO/embedded-practice.git
lenin@andres:~/embedded-practice$ git push -u origin main
error: src refspec main does not match any
error: failed to push some refs to 'https://github.com/TU_USUARIO/embedded-practice.git'
lenin@andres:~/embedded-practice$ git status
On branch master
nothing to commit, working tree clean
lenin@andres:~/embedded-practice$ git branch
* master
lenin@andres:~/embedded-practice$ git log --oneline
2d51790 (HEAD -> master) Initial Setup with Unity and Smoke test
lenin@andres:~/embedded-practice$ git branch -M main
lenin@andres:~/embedded-practice$ gh auth status
github.com
  ✓ Logged in to github.com account leninavb (/home/lenin/.config/gh/hosts.yml)
  - Active account: true
  - Git operations protocol: https
  - Token: gho_************************************
  - Token scopes: 'gist', 'read:org', 'repo', 'workflow'
lenin@andres:~/embedded-practice$ git remote set-url origin https://github.com/leninavb/embedded-practice.git
lenin@andres:~/embedded-practice$ git remote -v
origin  https://github.com/leninavb/embedded-practice.git (fetch)
origin  https://github.com/leninavb/embedded-practice.git (push)
lenin@andres:~/embedded-practice$ git push -u origin main
Enumerating objects: 213, done.
Counting objects: 100% (213/213), done.
Delta compression using up to 12 threads
Compressing objects: 100% (204/204), done.
Writing objects: 100% (213/213), 348.35 KiB | 12.01 MiB/s, done.
Total 213 (delta 52), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (52/52), done.
To https://github.com/leninavb/embedded-practice.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
lenin@andres:~/embedded-practice$ 