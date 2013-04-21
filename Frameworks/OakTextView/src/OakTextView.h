#import "GutterView.h"
#import <OakAppKit/OakView.h>
#import <editor/editor.h>
#import <buffer/buffer.h>
#import <theme/theme.h>
#import <document/document.h>
#import <oak/debug.h>

extern int32_t const NSWrapColumnWindowWidth;
extern int32_t const NSWrapColumnAskUser;
extern NSString* const kUserDefaultsDisableAntiAliasKey;

namespace bundles { struct item_t; typedef std::shared_ptr<item_t> item_ptr; }

enum folding_state_t { kFoldingNone, kFoldingTop, kFoldingCollapsed, kFoldingBottom };

@protocol OakTextViewDelegate <NSObject>
@optional
- (NSString*)scopeAttributes;
@end

PUBLIC @interface OakTextView : OakView <NSTextInput, NSTextFieldDelegate>
- (void)setDocument:(document::document_ptr const&)aDocument;

@property (nonatomic, weak) id <OakTextViewDelegate>        delegate;
@property (nonatomic) theme_ptr const&                      theme;
@property (nonatomic) NSCursor*                             ibeamCursor;
@property (nonatomic) NSFont*                               font;
@property (nonatomic) BOOL                                  antiAlias;
@property (nonatomic) size_t                                tabSize;
@property (nonatomic) BOOL                                  showInvisibles;
@property (nonatomic) BOOL                                  softWrap;
@property (nonatomic) BOOL                                  scrollPastEnd;
@property (nonatomic) BOOL                                  softTabs;
@property (nonatomic, readonly) BOOL                        continuousIndentCorrections;

@property (nonatomic, readonly) BOOL                        hasMultiLineSelection;
@property (nonatomic, readonly) BOOL                        hasSelection;
@property (nonatomic) NSString*                             selectionString;
- (IBAction)saveScratchMacro:(id)sender;

@property (nonatomic) BOOL                                  isMacroRecording;

- (GVLineRecord const&)lineRecordForPosition:(CGFloat)yPos;
- (GVLineRecord const&)lineFragmentForLine:(NSUInteger)aLine column:(NSUInteger)aColumn;

- (BOOL)filterDocumentThroughCommand:(NSString*)commandString input:(input::type)inputUnit output:(output::type)outputUnit;

- (NSPoint)positionForWindowUnderCaret;
- (scope::context_t const&)scopeContext;
- (folding_state_t)foldingStateForLine:(NSUInteger)lineNumber;

- (IBAction)toggleMacroRecording:(id)sender;
- (IBAction)toggleFoldingAtLine:(NSUInteger)lineNumber recursive:(BOOL)flag;
- (IBAction)toggleShowInvisibles:(id)sender;
- (IBAction)toggleScrollPastEnd:(id)sender;

- (IBAction)saveScratchMacro:(id)sender;

- (void)performBundleItem:(bundles::item_ptr const&)anItem;
@end
