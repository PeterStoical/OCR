> 开发环境 visual studio 13 community  opencv3.1

**包含OCR图像处理的程序相关技术（后续补充other skills and tesseract ocr开源引擎）**
https://github.com/tesseract-ocr
开发的意义：OCR在后端的单字识别模块已经相当高了，不管使用hog+svm组合，还是CNN。
目前，身份证、银行卡识别都采用约束型的方式进行图片采集，得以减少噪声提高整体识别率。

Image processing: 1)Rescaling. 2)Binarisation. 3)Noise Removal. 4)Rotation. / Deskewing. 5)Border Removal.

# 文件夹说明
## lsd_line  图像矫正程序
利用lsd检测直线，计算直线的交点。然后进行透射变换进行矫正。

## extract_text_from_postcard  明星片文字提取
该源码参考http://stackoverflow.com/questions/23506105/extracting-text-opencv

## extract_text_from_bankcard  银行卡号提取
先裁剪图片，消除非卡号所在区域的影响。


4年后，ocr有的新的发展...周末抽时间更新一下。
