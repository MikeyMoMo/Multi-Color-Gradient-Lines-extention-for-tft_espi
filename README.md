# Multi-Color-Gradient-Lines-extention-for-tft_espi

Now you can draw multi-color lines in any direction with a variable number of colors and a variable length either with or without stretching.  You can specify the length of each segment and it will be drawn that long (total of segments) or you can sepcify the length of the line and the segments will be stretched or squashed down to the length you speficy.

Here is a picture of what it looks like with several lines and several random length and directions lines.

There are two routines.  One is the original with the length of the line fixed by the total of the segments.  That one is names drawMultiBlendLine.
The other routine is drawMultiBlendLine2.  It has a mode that will produce a fixed length line just like drawMultiBlendLine and a mode where it will draw a line of a specified length and ignore the line segment lengths.  I probably need to document this better and I will do that and update the code and this file but you can probably figure it out yourself with the code comments that are there.  I just wanted to get this uploaded now, since it is working well and so fast.

The reason I wrote it as two routines is that I thought that drawMultiBlendLine2 would be too slow and only to be used if required but, it turns out, that drawMultiBlendLine2 is plenty fast and the speed difference cannot be noticed between the two.  So, probably, you should just use drawMultiBlendLine2 as it is about as fast as drawMultiBlendLine.

You can target either the tft layer or any sprite you created with tft_espi (the GREAT graphics handling set of routines from Bodmer).  It gives some color and sophistication to your projects.

I will have the sprite version soon.  I managed to forget to step the version and I really screwed it up.  Going back to a previous and bringing it forward again.  It was not midnight night and my brain was not working!

Enjoy,
Mikey the Midnight Coder

<img width="400" height="300" alt="multicolor gradient alphablend" src="https://github.com/user-attachments/assets/204e3a09-5cb1-42bc-ba22-86ed1e12f909" />
