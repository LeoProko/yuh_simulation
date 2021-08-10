import cv2
import os

def make_video(image_folder, video_name, fps):
    print('Starting make video from charts images')
    print('FPS:', fps)
    image_names = [img for img in os.listdir(image_folder)]
    image_names.sort()

    frame = cv2.imread(os.path.join(image_folder, image_names[0]))
    height, width, _ = frame.shape
    video = cv2.VideoWriter(video_name, 0, fps, (width, height))

    for image_name in image_names:
        video.write(cv2.imread(os.path.join(image_folder, image_name)))

    cv2.destroyAllWindows()
    video.release()
    print('Making video was successful')

def main():
    make_video('charts/map', 'visualization.avi', 10)

if __name__ == '__main__':
    main()
