VideosStream Console Application Overview:

This program is written to record video from the BlackMagic Decklink Video Acquisition Card and sync with LabStreamingLayer (https://github.com/sccn/labstreaminglayer). It will only work with cameras that work as BMD streaming devices, as specified in the BlackMagic API manual. (http://hackipedia.org/Software/Libraries/Black%20Magic%20Design/Decklink%20SDK/Blackmagic%20Decklink%20SDK%20(December%202012).pdf)

To build this program three separate packages are required: Boost, LSL, and the DeckLink SDK. Boost can be downloaded at http://www.boost.org/, LSL can be downloaded from the github linked above, and the DeckLink SDK can be retrieved from BlackMagic Design's website https://www.blackmagicdesign.com/.
Once downloaded, the locations of these packages must be specifed in the properties page of the VideosStream progject via File->Project Properties. 
