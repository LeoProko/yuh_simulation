if ! command -v ffmpeg
then
    sudo apt-get install ffmpeg
fi
python3 src/make_video.py
echo Starting compressing
ffmpeg -i visualization.avi visualization.mp4
rm visualization.avi
echo Succsessful compressing!
