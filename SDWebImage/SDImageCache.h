/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"

enum SDImageCacheType
{
    /**
     * The image wasn't available the SDWebImage caches, but was downloaded from the web.
     */
    SDImageCacheTypeNone = 0,
    /**
     * The image was obtained from the disk cache.
     */
    SDImageCacheTypeDisk,
    /**
     * The image was obtained from the disk cache.
     */
    SDImageCacheTypeMemory
};
typedef enum SDImageCacheType SDImageCacheType;

/**
 * SDImageCache maintains a memory cache and an optional disk cache. Disk cache write operations are performed
 * asynchronous so it doesn’t add unnecessary latency to the UI.
 */
@interface SDImageCache : NSObject

/**
 * The maximum length of time to keep an image in the cache, in seconds
 */
@property (assign, nonatomic) NSInteger maxCacheAge;

/** 
 * Change cache namespace
 */
@property (strong, nonatomic) NSString *nameSpace;

/**
 * Returns global shared cache instance
 *
 * @return SDImageCache global instance
 */
+ (SDImageCache *)sharedImageCache;

/**
 * Init a new cache store with a specific namespace
 *
 * @param ns The namespace to use for this cache store
 */
- (id)initWithNamespace:(NSString *)ns;

/**
 * Store an image into memory and disk cache at the given key.
 *
 * @param image The image to store
 * @param key The unique image cache key, usually it's image absolute URL
 */
- (void)storeImage:(UIImage *)image forKey:(NSString *)key;

/**
 * Store an image into memory and optionally disk cache at the given key.
 *
 * @param image The image to store
 * @param key The unique image cache key, usually it's image absolute URL
 * @param toDisk Store the image to disk cache if YES
 */
- (void)storeImage:(UIImage *)image forKey:(NSString *)key toDisk:(BOOL)toDisk;

/**
 * Store an image into memory and optionally disk cache at the given key.
 *
 * @param image The image to store
 * @param data The image data as returned by the server, this representation will be used for disk storage
 *             instead of converting the given image object into a storable/compressed image format in order
 *             to save quality and CPU
 * @param key The unique image cache key, usually it's image absolute URL
 * @param toDisk Store the image to disk cache if YES
 */
- (void)storeImage:(UIImage *)image imageData:(NSData *)data forKey:(NSString *)key toDisk:(BOOL)toDisk;


/** Move a cached file with the sourceURL to another url given by destURL
 *
 * @param sourceURL Source url to be moved
 * @param destURL Destination url to contain the cached image given by sourceURL
 * @param doneBlock Block to be called after the operation moves
 */
- (void)moveFileWithURL:(NSURL *)sourceURL toURL:(NSURL *)destURL done:(void (^)(NSError *error))doneBlock;

/** 
 * Move files from namespace to namespace
 * If destNamespace is nil we will use the default namespace
 */
- (void)moveFilesFromNamespace:(NSString *)sourceNameSpace
                   toNameSpace:(NSString *)destNameSpace
                          done:(void (^)(NSError *error))doneBlock;
 

/**
 * Query the disk cache asynchronousely.
 *
 * @param key The unique key used to store the wanted image
 */
- (void)queryDiskCacheForKey:(NSString *)key done:(void (^)(UIImage *image, SDImageCacheType cacheType))doneBlock;

- (void)queryDiskCacheForURL:(NSURL *)url done:(void (^)(UIImage *image, SDImageCacheType cacheType))doneBlock;

/**
 * Query the memory cache.
 *
 * @param key The unique key used to store the wanted image
 */
- (UIImage *)imageFromMemoryCacheForKey:(NSString *)key;

/**
 * Returns the image for the given fileURL
 *
 * @param fileURL Source URL
 * @return Image object or nil if it doesn't have any cached image
 */
- (UIImage *)imageForURL:(NSURL *)fileURL;

/**
 * Remove the image from memory and disk cache synchronousely
 *
 * @param key The unique image cache key
 */
- (void)removeImageForKey:(NSString *)key;

/**
 * Remove the image from memory and optionaly disk cache synchronousely
 *
 * @param key The unique image cache key
 * @param fromDisk Also remove cache entry from disk if YES
 */
- (void)removeImageForKey:(NSString *)key fromDisk:(BOOL)fromDisk;

/**
 * Clear all memory cached images
 */
- (void)clearMemory;

/**
 * Clear all disk cached images
 */
- (void)clearDisk;

/**
 * Remove all expired cached image from disk
 */
- (void)cleanDisk;

/**
 * Get the size used by the disk cache
 */
- (int)getSize;

/**
 * Get the number of images in the disk cache
 */
- (int)getDiskCount;

@end
