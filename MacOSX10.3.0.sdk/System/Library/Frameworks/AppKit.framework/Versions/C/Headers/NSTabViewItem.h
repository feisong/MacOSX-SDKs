/*
	NSTabViewItem.h
        Application Kit
        Copyright (c) 2000-2003, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSView.h>

@class NSColor, NSTabView, NSView;

typedef enum _NSTabState {
    NSSelectedTab = 0,
    NSBackgroundTab = 1,
    NSPressedTab = 2
} NSTabState;

typedef struct NSTabViewItemAuxiliary NSTabViewItemAuxiliaryOpaque;

@interface NSTabViewItem : NSObject <NSCoding>
{
    @private
    
    	/* Persistent properties */
    
    id			_identifier;    
    NSString		*_label;			// the label
    NSView		*_view;				// view to be displayed
    NSView		*_initialFirstResponder;	// initial first responder for that view
    NSColor		*_color;			// the color of the tab. By default [NSColor controlColor]
    NSTabView		*_tabView;			// back pointer to the tabView. Could be nil.

    	/* Non-persistent properties */
    
    NSTabState		_tabState;			// NSSelectedTab, NSBackgroundTab, or NSPressedTab
    NSView		*_lastKeyView;			// The "last" view in this items keyboard loop
    BOOL 		_hasCustomColor;		// YES if _color != [NSColor controlColor]
    BOOL		_labelSizeValid;		// YES if _labelSize is valid
    BOOL                _autoGeneratedIFR;
    
    NSSize		_labelSize;			// Cached label size. Valid if _labelSizeValid equal YES
    NSRect		_tabRect;			// Cached tabRect
    NSToolTipTag	_tabToolTipTag;			// Saved tool tip tag, for when text label is truncated.
    NSTabViewItemAuxiliaryOpaque *_auxiliaryStorage;
}

	/* Initialization */

- (id)initWithIdentifier:(id)identifier;

    	/* Getters */

- (id)identifier;
- (id)view;
- (id)initialFirstResponder;
- (NSString *)label;
- (NSColor *)color;
- (NSTabState)tabState;
- (NSTabView *)tabView;

    	/* Setters */

- (void)setIdentifier:(id)identifier;
- (void)setLabel:(NSString *)label;
- (void)setColor:(NSColor *)color;
- (void)setView:(NSView *)view;
- (void)setInitialFirstResponder:(NSView *)view;

	/* Tab Drawing/Measuring */

- (void)drawLabel:(BOOL)shouldTruncateLabel inRect:(NSRect)labelRect;
    // This method draws the tab label assuming a local coordinate system whose label axis runs along the x axis.
    // 'labelRect' is the area in between the curved end caps.
    // 'shouldTruncateLabel' is a hint that the label should be truncated.
    //    ie. if shouldTruncateLabel is YES, then labelRect.size < ceil([sizeOfLabel:YES])
    // Assume the label axis runs along the length of the label (perpendicular to the direction of the tab).

- (NSSize)sizeOfLabel:(BOOL)computeMin;
    // This method returns the minimum or nominal size of the tab label.  The width of the label is measured
    // along the label axis, and height is measured in the direction parallel to the tab direction.
    // 'computeMin' indicates whether you should return the minimum or
    //              nominal label size.  The returned value is used to
    //              compute the range of legal sizes for the tab label.

@end

