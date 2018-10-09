#!/bin/bash
rm -f *.so *.d *~ *.pcm
rm -f Event_Display.C
rm -f Batch_Job.C

ln -s Event_Display_$1.C Event_Display.C
ln -s Batch_$1.C Batch_Job.C