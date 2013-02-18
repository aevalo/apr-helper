require("myhello")
t = myhello.InitMyHello()
print(t)
print(t.greet)
t.greet()
t["greet"]()

print(t["foo"])
t["foo"] = "bar"
print(t["foo"])
