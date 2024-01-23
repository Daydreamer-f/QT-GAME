# README

### ver. 0.0.1(20230525)

+ 完善主界面基本框架
+ 明确一点：QT 只用来进行窗口与交互，不参与所有算法的构建，否则会非常困难。
+ 前端（为了方便 除了 text_page 我们不考虑做页面切换，直接新建页面即可，游戏默认全屏，页面边框美化一下就行）（xym）
  + Welcome_Page
    + NEW START
    + LOAD
    + EXIT
  + Main_Menu
    + 选课(button)
      + 课程列表
        + 课程详情
    + 活动(button)
      + 活动列表
        + 活动详情
    + 绩点查询(button)
    + 日程表(button)
    + 游戏规则(button)
    + 当前的数值（数字显示）
    + BACK
    + SAVE（button）
  + Warning_Page
    + 输出警告信息
    + 一个button
  + Text_Page（用于剧情说明）
    + 如果可以需要做成可翻页式
    + 一个按钮
  + （其实如果做不可翻页的这两可以合成一个，但是建议最好做成可翻页的要不然弹来弹去影响观感）
  + Game_Over_Page
+ 后端（hd&fys）
  + 为了易于修改，需要尽可能做到所有数据以文件的形式存储，而非写在代码中
  + 所有东西都以函数的形式，方便查询，方便合并
  + 主体需要做的：
    + 一个一周的日程表的东西
    + 一个选课系统一样的东西
      + 查询当前可以选择的课
      + 给出当前已选的课
      + 退选课程（可选）
    + 存档
      + 以周为单位进行存档
    + 数值的计算与查询
    + 事件记录
      + 连续做某事多少次
      + 一共做某事多少次
+ 文案&美工
+ 完成开始界面与游戏主界面的切换
+ 确认所有的交互逻辑
  + 数值
    + 绩点
    + 劳累值
    + 情绪
  + 课程
    + 课程列表
      + 课程（单击或hover显示详细信息）
        + 学分
        + 学时
        + 上课时间
          + 为了方便我们需要简化，如：
          + x 学分->在未来的若干天每天的同一/不同时刻上课
        + 考试时间
  + 活动
    + 活动列表（这一部分处理和课程完全相同）
      + 休闲
      + 玩游戏
      + 色色的事情（？）
      + 学习
        + 如果可以可以可以具体加上学习哪一门，加不了也没关系
      + 以及一些不定时出现的限定活动（别急，做不了就不做了）
  + 绩点详情查询（这个不急）
  + 日程表（这个可能急一些）
    + 希望能够显示未来七天你的所有日程
    + 为了简化时间段可以分为上午/下午/晚上 或者12/34/56/78/91011 这样的时间段，然后写一个表出来
  + 用户的操作逻辑
    + 第一步：选课（以周为单位）
      + 在每周开始之前选课（为了简便所以希望所有课程在本周内结束）
      + 选课之间不能冲突
        + 这里需要实时判断冲突，并将相应选项 disable 掉
    + 第二步：开启美好的一周！
      + 到达某个时间段
        + 如果有课（考试）
          + 询问是否翘课（考试不能翘）
            + 是
            + 选择活动
            + 否
            + 上课（可以有一些剧情）
        + 如果没课
          + 选择活动
          + 也可以有一些剧情
    + bonus：在某些数值到达某些节点时触发剧情
    + 回到第一步
  + 数值设计
    + 绩点
      + [0,4]，保留三位小数
      + 你听课的效率
        + 效率和听课时的劳累值、情绪相关（一个函数）
      + 你学习的效率
        + 效率和听课时的劳累值、情绪相关（一个函数）
      + 微微微小的random
      + 微小的与劳累值、情绪相关的参数
      + （最好是可以设计成一个合理的公式，这样可以针对每门课仅改变参数）
    + 劳累值
      + [0,100] 的整数，初始为 0
      + 听课，学习，考试+
      + 其余活动-
    + 情绪
      + [-100,100] 的整数，分数越大代表越开心，初始为 0
      + 学习、考试概率变化，更大概率-
      + 活动概率变化，更大概率+
      + 取得一门高绩点+
      + 取得一门低绩点-
  + 结局（成就系统不急）
    + 预计修完 X 学分后/若干周后自动结束（？我们也许设计不了这么多课程，但是可以只有名字没有剧情捏）
      + 这个具体不急，反正结算界面就是GAMEOVER+这个结局的名字，还是比较好做的
    + 对于某些数值达到某些极端情况，直接触发结局
    + 对于某些行为的特殊情况（如天天打游戏，涩涩过多之类的），直接触发结局（这个不急，但是会很有意思）
  + 音乐，音效
    + 这个更不急了
    + ~~（甚至打算自己手搓8-bit风格的音乐/音效）~~

### ver. 0.0.2 (20230601)

+ 完善所有事件的交互方式，统一采用 json 方式进行存储
+ 进行部分事件的编写
+ 进行整体测试
+ load 功能

### ver. 1.0.0 (20230604)

+ 美化
+ 音效
+ 