
# import spotipy
# from spotipy.oauth2 import SpotifyOAuth
# import os
# from dotenv import load_dotenv
#
#
# def get_track_uri(passed_index, passed_song_list):
#     passed_index = int(passed_index)
#     for element in passed_song_list:
#         if element.index == passed_index:
#             return element
#
#
# class Song:
#     def __init__(self, index, name, artist, url):
#         self.index = index
#         self.name = name
#         self.artist = artist
#         self.url = url
#
#
# load_dotenv()
#
# # Spotify Developer App Credentials
# CLIENT_ID = os.getenv('CLIENT_ID')
# CLIENT_SECRET = os.getenv('CLIENT_SECRET')
# REDIRECT_URI = 'http://localhost:8888/callback'  # Must match the one set in your Spotify Developer App
#
# # Spotify Device Name (the device you want to play the song on)
# DEVICE_NAME = 'fedora'
#
# # Initialize Spotipy with OAuth2
# sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=CLIENT_ID,
#                                                client_secret=CLIENT_SECRET,
#                                                redirect_uri=REDIRECT_URI,
#                                                scope='user-library-read user-read-playback-state user-modify-playback-state'))
#
# # Get a list of available devices
# devices = sp.devices()
#
# # Print the names of all available devices
# # for device in devices['devices']:
# #     print(f"Device Name: {device['name']}, Device ID: {device['id']}")
#
# # Input: Name of the song
# song_name = input("Enter the name of the song: ")
#
# # Search for the song
# results = sp.search(q=song_name, type='track', limit=6)
#
# search_results = results['tracks']['items']
# # print(search_results)
#
# if search_results:
#     index = 0
#     song_list = []
#     for item in search_results:
#         # Saving Variables
#         song_name = item['name']
#         song_artist = item['artists'][0]['name']
#         song_url = item['uri']
#
#         # Print Values
#         print(index)
#         print(song_name)
#         print(song_artist)
#         print()
#
#         # Saving song
#         song = Song(index, song_name, song_artist, song_url)
#         song_list.append(song)
#         index += 1
#
#     song_number = input("Enter the number of the song you want: ")
#
#     # track_uri_1 = results['tracks']['items'][0]['uri']
#     selected_song = get_track_uri(song_number, song_list)
#     track_uri = selected_song.url
#
#     print(f"Found '{song_name}'. Playing on '{DEVICE_NAME}'...")
#
#     # Get a list of available devices
#     devices = sp.devices()
#
#     for device in devices['devices']:
#         if device['name'] == DEVICE_NAME:
#             sp.start_playback(device_id=device['id'], uris=[track_uri])
#             print(f"Now playing on '{DEVICE_NAME}'")
#             break
#     else:
#         print(f"'{DEVICE_NAME}' not found among available devices.")
# else:
#     print(f"'{song_name}' not found on Spotify.")
