# A simple game for my Adv-Prog course

*C++ / SDL2*

<img src="img\Screenshot.png">

</br>

# Mô tả chung
Game thuộc dạng bắn súng tọa độ 2 người, bằng cách căn lực và góc theo vị trí và hướng gió. 

</br>

# Cài đặt

```bash
git clone https://github.com/lechienn/BTL-LTNC.git
```
```
mingw32-make
```

```
./main.exe
```

</br>

# Chi tiết trò chơi

<a href="https://youtu.be/QJrZAHFGXQA"> <img src ="https://img.shields.io/youtube/views/QJrZAHFGXQA?label=Youtube&style=social">
</a>

Mỗi nhân vật có 3 kỹ năng:

- Bắn 2 lần: nhận được 2 lượt chơi liên tiếp
- Tăng sát thương: phát bắn tiếp theo có sát thương cao hơn
- Hồi máu: hồi 1 lượng máu nhỏ và mất lượt

Sử dụng phím 1, 2, 3 để sử dụng kỹ năng, sử dụng phím Up, Down để căn góc, sử dụng phím Space để căn lực

</br>

# Các kỹ thuật lập trình được sử dụng
- Ngôn ngữ C++: lớp, mảng, con trỏ
- Đồ họa: SDL2.0, SDL_ttf, mixer, image

</br>

# Kết luận và hướng phát triển

- Gameplay và đồ họa còn đơn giản, đã biết áp dụng các kiến thức của môn học và thư viện đồ họa SDL2.
- Có tham khảo phần class TextureManager và cấu trúc class Game, phần còn lại tự phát triển.
- Phần lập trình chưa được tối ưu, rườm rà, chưa thiết kế được trước mối quan hệ giữa các đối tượng.
### Hướng phát triển
- Gameplay phức tạp hơn với nhiều chức năng khác như di chuyển, dịch chuyển, bộ kỹ năng đa dạng hơn đi kèm với thanh năng lượng.
- Nhiều lựa chọn bản đồ hơn (không còn bản đồ chỉ 1 mặt phẳng) với các địa hình khác nhau.