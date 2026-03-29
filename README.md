# 8-way-respond
8-channel responder based on 8051 (STC89C52) MCU, with countdown timer, foul detection, scoring system, LCD1602 display and buzzer alarm. 基于 51 单片机的八路抢答器，支持抢答计时、犯规检测、计分管理、LCD 显示与蜂鸣器提示，模块化代码，适合学习与实战。

## 设计一个供8名选手参加比赛的智力竞赛抢答器，要求如下
(1) 每名选手有一个抢答按钮，按钮的编号与选手的编号相对应。
(2) 抢答器具有第一个抢答信号的鉴别和数据锁存、显示的功能。抢答开始后，若有选手按下抢答按钮，则该选手指示灯亮，并在数码管上显示相应编号，扬声器发出声音提示。同时，电路应具备自锁功能，禁止其他选手再抢答，优先抢答选手的编号会一直保持到主持人将系统清0为止。
(3) 抢答器具有计分、显示功能。预置分数可由主持人设定，并显示在每名选手的计分牌上。选手答对加10分，答错扣10分。
(4) 抢答器具有定时抢答的功能。一次抢答的时间由主持人设定，在主持人发出抢答指令后，定时器立即进行减计时，并在显示器上显示，同时扬声器发出短暂声音提示，声音提示持续时间为0.5秒左右。
(5) 选手在设定的抢答时间内进行抢答，抢答有效，定时器停止工作，显示器显示选手编号和抢答时刻的时间，并保持到主持人将系统清0为止。
(6) 如果设定抢答的时间已到，却没有选手抢答，则本次抢答无效，系统进行短暂的报警，并禁止选手超时后抢答，定时显示器上显示00。
(7) 抢答器具有犯规提示功能。对提前抢答和超时抢答的选手，扬声器发出报警信号，并在显示器上显示其编号。

## 功能特性
八路选手独立抢答（S1-S8）
抢答倒计时（可自由设置 0-60s）
犯规检测（未开始/超时抢答自动提示）
选手分数管理（初始100分，支持±10分调整）
LCD1602 实时显示：抢答状态、剩余时间、当前分数、犯规编号
LED 指示灯：抢答成功对应选手灯点亮
蜂鸣器提示：开始/抢答成功/犯规/超时均有提示音
独立按键 + 矩阵按键双控制
状态重置、抢答启停、时间调整功能

## 硬件平台
1.主控：STC89C52 / 通用 8051 单片机
2.显示：LCD1602
3.输入：独立按键 ×2 + 矩阵按键 ×13
4.输出：LED 指示灯 ×8、无源蜂鸣器 ×1
5.引脚定义
6.蜂鸣器：P3^3
7.LED 端口：P2
8.矩阵按键 / 独立按键：标准 51 开发板接口

## 操作说明
1. K1：开始/暂停抢答
2. K2：重置所有状态（分数、时间、选手）
3. S1-S8：选手抢答按键
4. S9：切换当前计分选手
5. S10：分数 +10
6. S11：分数 -10
7. S12：抢答时间 +1s
8. S13：抢答时间 -1s

## English translation

## 8-way-respond
8-channel responder based on 8051 (STC89C52) MCU, with countdown timer, foul detection, scoring system, LCD1602 display and buzzer alarm. Modular code, suitable for learning and practical applications.

## Design an intelligent competition responder for 8 players, requirements are as follows
(1) Each player has a response button, and the button number corresponds to the player number.
(2) The responder can identify, latch and display the first valid response signal. After the response starts, if a player presses the button, the corresponding indicator lights up, the player number is displayed, and the buzzer sounds. The system locks automatically to prevent other players from responding. The priority player number remains until the host resets the system.
(3) The responder supports scoring and display functions. The initial score can be set by the host and shown on each player’s scoreboard. Add 10 points for correct answers and deduct 10 points for wrong answers.
(4) The responder has a timed response function. The response time is set by the host. After the host starts the response, the timer counts down and displays the remaining time. The buzzer gives a short prompt (about 0.5 seconds).
(5) If a player responds within the set time, the response is valid, the timer stops, and the display shows the player number and remaining time until the host resets the system.
(6) If no player responds when time is up, the response is invalid. The system alarms briefly, prohibits late responses, and displays 00 on the timer.
(7) The responder has a foul prompt function. For early or late responses, the buzzer alarms and displays the violating player number.

## Features
1.8 independent player response channels (S1-S8)
2.Countdown timer (adjustable 0-60s)
3.Foul detection (auto alert for early/late response)
4.Player scoring management (initial 100 points, ±10 points adjustment)
5.LCD1602 real-time display: response status, remaining time, current score, foul number
6.LED indicators: corresponding LED lights up when response succeeds
7.Buzzer prompts: sounds for start, success, foul and timeout
8.Dual control: independent keys + matrix keys
9.System reset, response start/pause, time adjustment

## Hardware Platform
1.Main controller: STC89C52 / general 8051 MCU
2.Display: LCD1602
3.Input: 2 independent keys + 13 matrix keys
4.Output: 8 LED indicators, 1 passive buzzer
5.Pin definitions
6.Buzzer: P3^3
7.LED port: P2
8.Matrix keys / independent keys: standard 51 development board interface

## Operation Instructions
1.K1: Start / Pause response
2.K2: Reset all status (score, time, player)
3.S1-S8: Player response buttons
4.S9: Switch current scoring player
5.S10: Score +10
6.S11: Score -10
7.S12: Response time +1s
8: Response time -1s

