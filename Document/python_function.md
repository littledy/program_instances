`os`库

```python
os.getcwd() # 获取当前目录
os.path.abspath(os.path.dirname(__file__))	# 获取目录绝对路径

# 获取上级目录
os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
os.path.abspath(os.path.dirname(os.getcwd()))
os.path.abspath(os.path.join(os.getcwd(), '..'))

# 获取上上级目录
os.path.abspath(os.path.join(os.getcwd(), "../.."))

os.chdir("dst")	# 改变当前目录
```



`pandas`库

```python
df = pandas.read_csv(path)

df.shape
```

