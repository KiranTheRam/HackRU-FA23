import spotipy
from spotipy.oauth2 import SpotifyOAuth
import os
from dotenv import load_dotenv
import serial
import requests
import time

# ser = serial.Serial('\\\\.\\COM5', 9600, timeout=0.15)
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.15)

load_dotenv()

# Spotify Developer App Credentials
CLIENT_ID = os.getenv('CLIENT_ID')
CLIENT_SECRET = os.getenv('CLIENT_SECRET')

REDIRECT_URI = 'http://localhost:8888/callback'  # Must match the one set in your Spotify Developer App

# Spotify Device Name (the device you want to play the song on)
DEVICE_NAME = 'fedora'

# Initialize Spotipy with OAuth2
sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=CLIENT_ID,
                                               client_secret=CLIENT_SECRET,
                                               redirect_uri=REDIRECT_URI,
                                               scope='user-library-read user-read-playback-state user-modify-playback-state'))


def sensor_val():
    data = ser.read(100).split(b'\n')
    data = data[len(data) - 2]
    data = data.rstrip()
    return int(data)


class Song:
    def __init__(self, index, name, artist, url):
        self.index = index
        self.name = name
        self.artist = artist
        self.url = url


def search_and_play_song(song_name):
    # Input: Name of the song
    # song_name = input("Enter the name of the song: ")

    # Search for the song
    results = sp.search(q=song_name, type='track', limit=6)
    search_results = results['tracks']['items']

    if search_results:
        song_list = [Song(index, item['name'], item['artists'][0]['name'], item['uri']) for index, item in
                     enumerate(search_results)]

        for index, song in enumerate(song_list):
            print(f"{index}\n{song.name}\n{song.artist}\n")

        serial_list = f"{song_list[0].name},{song_list[0].artist},{song_list[1].name},{song_list[1].artist},{song_list[2].name},{song_list[2].artist},{song_list[3].name},{song_list[3].artist},{song_list[4].name},{song_list[4].artist},{song_list[5].name},{song_list[5].artist}"

        # TODO: Send serial_list to serial device

        # Get the selected number from serial device. Start with an
        song_number = None

        while True:
            if ser.inWaiting() > 0:
                song_number = sensor_val()
            break

        # song_number = input("Enter the number of the song you want: ")

        try:
            selected_song = song_list[song_number]

            print(f"Found '{selected_song.name}'. Trying playback on '{DEVICE_NAME}'...")

            # Get a list of available devices
            devices = sp.devices()

            # TODO: Remove after selecting proper device
            print(devices)

            for device in devices['devices']:
                if device['name'] == DEVICE_NAME:
                    sp.start_playback(device_id=device['id'], uris=[selected_song.url])
                    print(f"Now playing on '{DEVICE_NAME}'")
                    break
            else:
                print(f"'{DEVICE_NAME}' not found among available devices.")
        except (ValueError, IndexError):
            print("Invalid input or song number not found.")
    else:
        print(f"'{song_name}' not found on Spotify.")

# if __name__ == "__main__":
#     search_and_play_song()
