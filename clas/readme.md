
## API KEY

建立 config.py

添加key = 'your key'

---

## 返回参数

| 返回参数 | 类型   | 说明     |
| -------- | ------ | -------- |
| name     | string | 垃圾名称 |
| type     | int    | 垃圾分类,0为可回收,1为有害,2为厨余垃圾,3为其他垃圾 |
| aipre    | int    | 智能预判, 0为正常结果,1为预判结果 |
| explain  | string | 分类解释 |
| contain  | string | 包含类型 |
| tip      | string | 投放提示 |

