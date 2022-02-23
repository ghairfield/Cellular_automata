## Changes for Feature-CGL

### Major changes

- Hoisted game logic out of `Display` class
- Added namespace `CA` to all classes
- Added move semantics
  - The `CGL` class no longer _owns_ the display information and now operates
    on it.
  - The `Display` class no longer _owns_ a copy of the display and only
    operates on it.
- Created `Unit` class to represent the cells. Contains pixel to cell and
  related functionality.

### Smaller changes

- Changed `unsigned int` to `uint32_t`
- Unified naming convention across classes
- Added more documentation
- Added `.gitignore`
