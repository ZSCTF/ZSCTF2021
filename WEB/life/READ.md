### 水题

### 考察php的生命周期

### payload：a:2:{i:0;O:9:"superGate":1:{s:3:"gay";b:1;};i=0;N;}

### 反序列化的时候，只要类的生命周期完整结束就可以触发__destruct()方法

### 而在if中抛出了一个异常阻止了__destruct()方法的触发了，那么我们只需要将类的生命周期结束就可以获得flag了。

### payload的方式是反序列化了一个数组，利用数组将类置空，将类的生命周期结束

