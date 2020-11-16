# vscode打开出现问题解决方案





# 一般使用指令
 STM32_Programmer_CLI -c port=SWD -d build/PIONEER.bin 0x8000000 -s




echo "# PIONEER" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/WithTenet/PIONEER.git
git push -u origin main
                


# 开发日记
2020 11 14 
今天增加了TIM1的4个通道捕获 // 应该加锁进行访问。
TIM8的四通道输出还没有完成  // 应该加锁